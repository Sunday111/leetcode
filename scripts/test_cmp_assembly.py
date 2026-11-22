from contextlib import redirect_stderr, redirect_stdout
import io
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest
from unittest.mock import patch

import cmp_assembly
from print_assembly import symbol_body
from test_print_assembly import ASSEMBLY


class AssemblyComparisonTests(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory(prefix="assembly-compare-", dir="/tmp")
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)

    def compare(self, left, right, *, suffix=".s", function="first", options=()):
        paths = [self.root / f"{name} source{suffix}" for name in ("left", "right")]
        for path, source in zip(paths, (left, right)):
            path.write_text(source, encoding="utf-8")
        stdout, stderr = io.StringIO(), io.StringIO()
        with redirect_stdout(stdout), redirect_stderr(stderr):
            status = cmp_assembly.main([
                *([function] if function else []), *map(str, paths), *options])
        return status, stdout.getvalue(), stderr.getvalue()

    def test_identical_raw_function_ignores_neighbouring_functions(self):
        status, output, error = self.compare(
            ASSEMBLY, ASSEMBLY.replace("second:\n    ret", "second:\n    nop\n    ret"),
            options=["--no-filter-metadata", "--no-demangle"])
        self.assertEqual(status, 0, error)
        self.assertEqual(output, symbol_body(ASSEMBLY, "first"))

    def test_raw_difference_has_source_names_and_changed_instruction(self):
        status, output, error = self.compare(
            ASSEMBLY, ASSEMBLY.replace("jmp .Ldone", "nop"),
            options=["--no-filter-metadata", "--no-demangle"])
        self.assertEqual(status, 1, error)
        self.assertIn("--- " + str(self.root / "left source.s"), output)
        self.assertIn("+++ " + str(self.root / "right source.s"), output)
        self.assertIn("-    jmp .Ldone", output)
        self.assertIn("+    nop", output)

    def test_missing_symbol_is_error_not_difference(self):
        status, output, error = self.compare(
            ASSEMBLY, ASSEMBLY, function="absent")
        self.assertEqual(status, 2)
        self.assertEqual(output, "")
        self.assertIn("No emitted label", error)

    def test_aliases_are_display_only_and_can_be_disabled(self):
        body = "first:\n    call f(std::basic_string_view<char, std::char_traits<char>>)\n"
        with patch.object(cmp_assembly, "render_function", return_value=body):
            status, output, error = self.compare(ASSEMBLY, ASSEMBLY)
            self.assertEqual(status, 0, error)
            self.assertIn("f(std::string_view)", output)
            for flag in ("--no-filter-types", "--no-demangle"):
                status, output, error = self.compare(ASSEMBLY, ASSEMBLY, options=[flag])
                self.assertEqual(status, 0, error)
                self.assertEqual(output, body)

    def test_alias_collisions_preserve_full_diff_and_other_changes(self):
        left = ("first:\n    call f(std::basic_string<char>)\n"
                "    call g(std::basic_string_view<char>)\n    ret\n")
        right = ("first:\n    call f(std::__cxx11::basic_string<char>)\n"
                 "    call g(std::basic_string_view<char>)\n    nop\n    ret\n")
        with patch.object(cmp_assembly, "render_function", side_effect=[left, right]):
            status, output, error = self.compare(ASSEMBLY, ASSEMBLY)
        self.assertEqual(status, 1, error)
        self.assertIn("-    call f(std::basic_string<char>)", output)
        self.assertIn("+    call f(std::__cxx11::basic_string<char>)", output)
        self.assertIn("call g(std::string_view)", output)
        self.assertIn("+    nop", output)

    def test_overloads_remain_distinct_with_short_names(self):
        with patch.object(cmp_assembly, "render_function", side_effect=[
            "first:\n    call f(std::basic_string_view<char> const&)\n",
            "first:\n    call f(std::basic_string_view<wchar_t> const&)\n",
        ]):
            status, output, error = self.compare(ASSEMBLY, ASSEMBLY)
        self.assertEqual(status, 1, error)
        self.assertIn("-    call f(std::string_view const&)", output)
        self.assertIn("+    call f(std::wstring_view const&)", output)

    def test_highlighting_keeps_comparison_plain_and_selects_output_language(self):
        options = ["--no-filter-metadata", "--no-demangle", "--color=always"]
        with patch.object(cmp_assembly, "write_output") as display, \
                patch.object(cmp_assembly, "write_difference") as display_diff:
            status, _, error = self.compare(ASSEMBLY, ASSEMBLY, options=options)
            self.assertEqual(status, 0, error)
            display.assert_called_once_with(symbol_body(ASSEMBLY, "first"), color="always")
            display_diff.assert_not_called()
            display.reset_mock()
            status, _, error = self.compare(
                ASSEMBLY, ASSEMBLY.replace("jmp .Ldone", "nop"), options=options)
            self.assertEqual(status, 1, error)
            display.assert_not_called()
            display_diff.assert_called_once()
            self.assertEqual(display_diff.call_args.kwargs,
                             {"color": "always", "side_by_side": True})
            self.assertIn("@@", display_diff.call_args.args[0])

    def test_delta_receives_plain_diff_with_side_by_side_and_inherits_terminal(self):
        with patch.object(cmp_assembly, "color_enabled", return_value=True), \
                patch.object(cmp_assembly.shutil, "which", return_value="/usr/bin/delta"), \
                patch.object(cmp_assembly.subprocess, "run", return_value=
                             subprocess.CompletedProcess([], 0)) as run:
            cmp_assembly.write_difference("diff text\n")
            run.assert_called_once_with(["/usr/bin/delta", "--side-by-side"],
                                        input="diff text\n", text=True)

    def test_unified_fallback_for_missing_delta_disabled_layout_or_plain_output(self):
        for enabled, installed, layout in ((True, None, True),
                                           (True, "/usr/bin/delta", False),
                                           (False, "/usr/bin/delta", True)):
            with self.subTest(enabled=enabled, installed=installed, layout=layout), \
                    patch.object(cmp_assembly, "color_enabled", return_value=enabled), \
                    patch.object(cmp_assembly.shutil, "which", return_value=installed), \
                    patch.object(cmp_assembly, "write_output") as display, \
                    patch.object(cmp_assembly.subprocess, "run") as run:
                cmp_assembly.write_difference("diff text\n", side_by_side=layout)
                display.assert_called_once_with("diff text\n", color="auto", language="diff")
                run.assert_not_called()

    def test_delta_failure_is_reported(self):
        with patch.object(cmp_assembly, "color_enabled", return_value=True), \
                patch.object(cmp_assembly.shutil, "which", return_value="/usr/bin/delta"), \
                patch.object(cmp_assembly.subprocess, "run", return_value=
                             subprocess.CompletedProcess([], 3)):
            with self.assertRaisesRegex(ValueError, "delta exited with status 3"):
                cmp_assembly.write_difference("diff text\n")

    @unittest.skipUnless(all(shutil.which(tool) for tool in
                            ("clang++", "llvm-objdump", "llvm-cxxfilt")),
                         "Clang and LLVM tools are required")
    def test_compiled_default_ignores_debug_paths_and_preserves_changes(self):
        source = "struct Solution { int run(const int* p) const { return *p + 1; } };"
        # Separate compilations must not differ just because their temporary
        # object paths, source paths or debug metadata differ.
        status, output, error = self.compare(
            source, "\n// Different source layout\n" + source,
            suffix=".hpp", function="Solution::run", options=["--flag=-g"])
        self.assertEqual(status, 0, error + output)
        self.assertEqual(output.count("<Solution::run(int const*) const>:"), 1)
        status, output, error = self.compare(
            source, source.replace("+ 1", "+ 7"), suffix=".hpp",
            function="Solution::run", options=["--syntax=intel"])
        self.assertEqual(status, 1, error)
        self.assertIn("@@", output)
        self.assertIn("Solution::run", output)
        self.assertNotIn("leetcode-disassembly-", output)

    @unittest.skipUnless(all(shutil.which(tool) for tool in
                            ("clang++", "llvm-objdump", "llvm-cxxfilt")),
                         "Clang and LLVM tools are required")
    def test_explicit_overload_address_and_shared_compiler_options(self):
        source = ("inline int pick(int x) {return x+1;} "
                  "inline double pick(double x) {return x+2;}")
        status, output, error = self.compare(
            source, source, suffix=".hpp", function=None,
            options=["--address", "static_cast<int (*)(int)>(&pick)",
                     "--no-asan", "--no-demangle", "--opt=O3",
                     "--flag=-mtune=native"])
        self.assertEqual(status, 0, error + output)

    @unittest.skipUnless(shutil.which("clang++"), "clang++ is required")
    def test_compilation_failure_reports_error_without_partial_diff(self):
        status, output, error = self.compare(
            "not C++;", "not C++;", suffix=".hpp", function="missing")
        self.assertEqual(status, 2)
        self.assertEqual(output, "")
        self.assertIn("error:", error)


if __name__ == "__main__":
    unittest.main()
