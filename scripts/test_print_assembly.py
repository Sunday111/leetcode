from pathlib import Path
import shutil
import tempfile
import unittest

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

    @unittest.skipUnless(shutil.which("g++"), "g++ is required")
    def test_gcc_function_pointer(self):
        symbol, body = self.compile(
            "inline unsigned increment(unsigned x) noexcept {return x+1;}",
            "&increment", compiler="g++", asan=False)
        self.assertEqual(symbol, "_Z9incrementj")
        self.assertIn("ret", body)


if __name__ == "__main__":
    unittest.main()
