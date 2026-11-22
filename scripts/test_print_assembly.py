from contextlib import redirect_stdout
import io
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
from unittest.mock import patch

import print_assembly


ASSEMBLY = """
.type first,@function
first:
    jmp .Ldone
.Ldone:
    ret
.size first, .-first
.cfi_endproc
.type second,@function
second:
    ret
.size second, .-second
assembly_target:
    .quad first
    .quad 0
.size assembly_target, 16
"""


class AssemblyExtractionTests(unittest.TestCase):
    def test_selects_member_pointer_target_without_neighbouring_functions(self):
        symbol = print_assembly.target_function(ASSEMBLY)
        self.assertEqual(symbol, "first")
        body = print_assembly.symbol_body(ASSEMBLY, symbol)
        self.assertIn(".Ldone:\n", body)
        self.assertTrue(body.endswith(".cfi_endproc\n"))
        self.assertNotIn("second", body)
        self.assertNotIn("assembly_target", body)

    def test_resolves_function_alias(self):
        assembly = ASSEMBLY.replace(".quad first", ".quad alias")
        assembly += ".type alias,@function\n.set alias, first\n"
        self.assertEqual(print_assembly.target_function(assembly), "first")
        self.assertEqual(print_assembly.symbol_body(assembly, "alias"),
                         print_assembly.symbol_body(assembly, "first"))

    def test_gcc_object_size_precedes_its_label(self):
        assembly = ASSEMBLY.replace(".size assembly_target, 16\n", "")
        assembly = assembly.replace("assembly_target:\n",
                                    ".size assembly_target, 16\nassembly_target:\n")
        assembly += ".section .data\nother_pointer:\n.quad second\n"
        self.assertEqual(print_assembly.target_function(assembly), "first")

    def test_missing_function_or_size_reports_failure(self):
        with self.assertRaisesRegex(ValueError, "No emitted label"):
            print_assembly.symbol_body(ASSEMBLY, "absent")
        with self.assertRaisesRegex(ValueError, "No ELF .size"):
            print_assembly.symbol_body("first:\nret\n", "first")

    def test_virtual_pointer_is_not_mistaken_for_a_function(self):
        with self.assertRaisesRegex(ValueError, "Virtual member pointers"):
            print_assembly.target_function(ASSEMBLY.replace(".quad first", ".quad 1"))

    def test_alias_cycle_reports_failure(self):
        with self.assertRaisesRegex(ValueError, "Cyclic"):
            print_assembly.resolve_alias(".set a, b\n.set b, a\n", "a")


class AssemblyHighlightingTests(unittest.TestCase):
    def display(self, *, terminal=False, environment=None, **options):
        output = io.StringIO()
        with redirect_stdout(output), patch.object(output, "isatty", return_value=terminal), \
                patch.dict("os.environ", environment or {}, clear=True):
            print_assembly.write_output("mov eax, 1\nret\n", **options)
        return output.getvalue()

    def test_redirected_disabled_and_no_color_output_stays_plain(self):
        with patch.object(print_assembly.shutil, "which") as which:
            for options in ({}, {"terminal": True, "color": "never"},
                            {"terminal": True, "environment": {"NO_COLOR": "1"}},
                            {"terminal": True, "environment": {"TERM": "dumb"}}):
                with self.subTest(options=options):
                    self.assertEqual(self.display(**options), "mov eax, 1\nret\n")
            which.assert_not_called()

    def test_missing_bat_falls_back_to_plain_output(self):
        with patch.object(print_assembly.shutil, "which", return_value=None), \
                patch.object(print_assembly.subprocess, "run") as run:
            self.assertEqual(self.display(terminal=True), "mov eax, 1\nret\n")
            run.assert_not_called()

    def test_terminal_and_forced_color_delegate_to_bat(self):
        highlighted = "\x1b[31mmov eax, 1\x1b[0m\nret\n"
        with patch.object(print_assembly.shutil, "which", return_value="/usr/bin/bat"), \
                patch.object(print_assembly.subprocess, "run", return_value=
                             subprocess.CompletedProcess([], 0, highlighted, "")) as run:
            self.assertEqual(self.display(terminal=True), highlighted)
            self.assertIn("asm", run.call_args.args[0])
            self.assertIn("--paging=never", run.call_args.args[0])
            self.assertEqual(run.call_args.kwargs["input"], "mov eax, 1\nret\n")
            self.assertEqual(self.display(color="always", language="diff",
                                         environment={"NO_COLOR": "1"}), highlighted)
            self.assertIn("diff", run.call_args.args[0])

    def test_failed_highlighter_preserves_plain_output(self):
        with patch.object(print_assembly.shutil, "which", return_value="/usr/bin/bat"), \
                patch.object(print_assembly.subprocess, "run") as run:
            run.return_value = subprocess.CompletedProcess([], 1, "partial", "failed")
            self.assertEqual(self.display(terminal=True), "mov eax, 1\nret\n")
            run.side_effect = OSError("bat disappeared")
            self.assertEqual(self.display(terminal=True), "mov eax, 1\nret\n")

    @unittest.skipUnless(shutil.which("bat"), "bat is required")
    def test_installed_bat_emits_ansi_for_assembly_and_diff(self):
        for language in ("asm", "diff"):
            with self.subTest(language=language):
                output = io.StringIO()
                text = ("mov eax, 1\nret\n" if language == "asm" else
                        "--- old\n+++ new\n@@ -1 +1 @@\n-ret\n+nop\n")
                with redirect_stdout(output):
                    print_assembly.write_output(text, color="always", language=language)
                self.assertIn("\x1b[", output.getvalue())


@unittest.skipUnless(shutil.which("clang++"), "clang++ is required")
class AssemblyCompilationTests(unittest.TestCase):
    def compile(self, declaration, address, **options):
        with tempfile.TemporaryDirectory(prefix="assembly-test-", dir="/tmp") as tmp:
            source = Path(tmp) / "with spaces.hpp"
            source.write_text(declaration, encoding="utf-8")
            assembly = print_assembly.compile_assembly(source, address, **options)
            symbol = print_assembly.target_function(assembly)
            return symbol, print_assembly.symbol_body(assembly, symbol)

    def test_const_noexcept_template_method_is_emitted(self):
        symbol, body = self.compile(
            "struct Sample { template<unsigned N> constexpr unsigned "
            "run(unsigned x) const noexcept {return x + N;} };",
            "&Sample::run<64>")
        self.assertIn("Sample", symbol)
        self.assertIn("ret", body)
        self.assertNotIn("asan.module_ctor:", body)

    def test_explicit_address_resolves_overload(self):
        symbol, body = self.compile(
            "inline int pick(int x) {return x+1;} "
            "inline double pick(double x) {return x+2;}",
            "static_cast<int (*)(int)>(&pick)", asan=False,
            opt="O3", syntax="intel", flags=["-mtune=native"])
        self.assertEqual(symbol, "_Z4picki")
        self.assertIn("ret", body)

    def test_compilation_error_is_reported(self):
        with self.assertRaisesRegex(ValueError, "error:"):
            self.compile("not valid C++;", "&missing")

    def test_missing_or_disabled_ccache_uses_compiler_directly(self):
        with patch.object(print_assembly.shutil, "which", return_value=None) as which:
            symbol, body = self.compile("inline int f() { return 1; }", "&f")
            self.assertEqual(symbol, "_Z1fv")
            self.assertIn("ret", body)
            which.assert_called_once_with("ccache")
        with patch.object(print_assembly.shutil, "which") as which:
            symbol, _ = self.compile("inline int f() { return 1; }", "&f", cache=False)
            self.assertEqual(symbol, "_Z1fv")
            which.assert_not_called()

    @unittest.skipUnless(shutil.which("ccache"), "ccache is required")
    def test_ccache_hits_and_invalidates_when_header_changes(self):
        with tempfile.TemporaryDirectory(prefix="assembly-cache-test-", dir="/tmp") as tmp:
            root = Path(tmp)
            config = root / "ccache.conf"
            config.write_text("", encoding="utf-8")
            source = root / "sample.hpp"
            source.write_text("inline int f() { return 1; }", encoding="utf-8")
            with patch.dict(os.environ, {"CCACHE_DIR": str(root / "cache"),
                                        "CCACHE_CONFIGPATH": str(config),
                                        "CCACHE_DISABLE": "", "CCACHE_RECACHE": ""}):
                # Empty boolean environment values are still set to ccache;
                # remove inherited bypasses so this test exercises the cache.
                os.environ.pop("CCACHE_DISABLE")
                os.environ.pop("CCACHE_RECACHE")
                first = print_assembly.compile_assembly(source, "&f", flags=["-g"])
                second = print_assembly.compile_assembly(source, "&f", flags=["-g"])
                self.assertEqual(first, second)
                stats = subprocess.run(["ccache", "--print-stats"], check=True,
                                       capture_output=True, text=True).stdout
                counters = dict(line.split() for line in stats.splitlines())
                self.assertGreater(int(counters["direct_cache_hit"]) +
                                   int(counters["preprocessed_cache_hit"]), 0)
                source.write_text("inline int f() { return 7; }", encoding="utf-8")
                changed = print_assembly.compile_assembly(source, "&f", flags=["-g"])
                self.assertNotEqual(print_assembly.symbol_body(first, "_Z1fv"),
                                    print_assembly.symbol_body(changed, "_Z1fv"))

    @unittest.skipUnless(shutil.which("llvm-objdump"), "llvm-objdump is required")
    @unittest.skipUnless(shutil.which("llvm-cxxfilt"), "llvm-cxxfilt is required")
    def test_default_filter_preserves_calls_and_full_saved_assembly(self):
        with tempfile.TemporaryDirectory(prefix="assembly-test-", dir="/tmp") as tmp:
            source = Path(tmp) / "sample.hpp"
            saved = Path(tmp) / "full.s"
            source.write_text(
                "inline int read_value(const int* p) { return *p; }\n"
                "[[gnu::used]] int neighbour(int x) { return x + 1; }\n",
                encoding="utf-8")
            output = io.StringIO()
            with redirect_stdout(output):
                status = print_assembly.main([
                    str(source), "read_value", "--flag=-g", "--syntax=intel",
                    "--save-assembly", str(saved)])
            self.assertEqual(status, 0)
            body = output.getvalue()
            self.assertIn("<read_value(int const*)>:", body)
            self.assertNotIn("<_Z10read_valuePKi", body)
            self.assertIn("__asan_report_load4", body)
            self.assertNotIn("neighbour", body)
            self.assertNotIn(".cfi_", body)
            self.assertNotIn(".loc", body)
            self.assertNotIn(".size", body)
            self.assertIn(".cfi_", saved.read_text(encoding="utf-8"))
            self.assertIn(".loc", saved.read_text(encoding="utf-8"))

            output = io.StringIO()
            with redirect_stdout(output):
                status = print_assembly.main([
                    str(saved), "_Z10read_valuePKi", "--filter-metadata",
                    "--no-demangle"])
            self.assertEqual(status, 0)
            self.assertIn("<_Z10read_valuePKi>:", output.getvalue())

    def test_filter_can_be_disabled(self):
        with tempfile.TemporaryDirectory(prefix="assembly-test-", dir="/tmp") as tmp:
            source = Path(tmp) / "sample.s"
            source.write_text(ASSEMBLY, encoding="utf-8")
            output = io.StringIO()
            with redirect_stdout(output):
                status = print_assembly.main([
                    str(source), "first", "--no-filter-metadata", "--no-demangle"])
            self.assertEqual(status, 0)
            self.assertEqual(output.getvalue(),
                             print_assembly.symbol_body(ASSEMBLY, "first"))

    @unittest.skipUnless(shutil.which("llvm-cxxfilt"), "llvm-cxxfilt is required")
    def test_type_alias_display_preserves_overload_selection_and_full_saved_text(self):
        with tempfile.TemporaryDirectory(prefix="assembly-test-", dir="/tmp") as tmp:
            source = Path(tmp) / "overloads.s"
            saved = Path(tmp) / "saved.s"
            narrow = "_Z4pickSt17basic_string_viewIcSt11char_traitsIcEE"
            wide = "_Z4pickSt17basic_string_viewIwSt11char_traitsIwEE"
            assembly = ASSEMBLY.replace("first", narrow).replace("second", wide)
            source.write_text(assembly, encoding="utf-8")
            for options, expected in (
                ([], "pick(std::string_view):"),
                (["--no-filter-types"],
                 "pick(std::basic_string_view<char, std::char_traits<char>>):"),
                (["--no-demangle"], narrow + ":"),
            ):
                with self.subTest(options=options):
                    output = io.StringIO()
                    with redirect_stdout(output):
                        status = print_assembly.main([
                            str(source), narrow, "--no-filter-metadata",
                            "--save-assembly", str(saved), *options])
                    self.assertEqual(status, 0)
                    self.assertIn(expected, output.getvalue())
                    self.assertNotIn("wstring_view", output.getvalue())
                    self.assertEqual(saved.read_text(encoding="utf-8"), assembly)

    @unittest.skipUnless(shutil.which("llvm-cxxfilt"), "llvm-cxxfilt is required")
    def test_demangling_preserves_exact_overload_selection(self):
        with tempfile.TemporaryDirectory(prefix="assembly-test-", dir="/tmp") as tmp:
            source = Path(tmp) / "overloads.s"
            source.write_text(ASSEMBLY.replace("first", "_Z4pickii")
                              .replace("second", "_Z4pickdd"), encoding="utf-8")
            output = io.StringIO()
            with redirect_stdout(output):
                status = print_assembly.main([
                    str(source), "_Z4pickii", "--no-filter-metadata"])
            self.assertEqual(status, 0)
            self.assertIn("pick(int, int):", output.getvalue())
            self.assertNotIn("pick(double, double)", output.getvalue())
            self.assertNotIn("_Z4pickii", output.getvalue())

    @unittest.skipUnless(shutil.which("g++"), "g++ is required")
    def test_gcc_function_pointer(self):
        symbol, body = self.compile(
            "inline unsigned increment(unsigned x) noexcept {return x+1;}",
            "&increment", compiler="g++", asan=False)
        self.assertEqual(symbol, "_Z9incrementj")
        self.assertIn("ret", body)


if __name__ == "__main__":
    unittest.main()
