import unittest

from assembly_types import shorten_common_types


class AssemblyTypeTests(unittest.TestCase):
    def test_string_and_view_aliases_for_all_standard_character_types(self):
        for char, prefix in (("char", ""), ("wchar_t", "w"), ("char8_t", "u8"),
                             ("char16_t", "u16"), ("char32_t", "u32")):
            for kind in ("string", "string_view"):
                arguments = [char, f"{char}, std::char_traits<{char}>"]
                if kind == "string":
                    arguments.append(f"{arguments[-1]}, std::allocator<{char}>")
                for args in arguments:
                    with self.subTest(kind=kind, args=args):
                        self.assertEqual(shorten_common_types(f"std::basic_{kind}<{args}>"),
                                         f"std::{prefix}{kind}")

    def test_stream_aliases(self):
        for kind in ("ios", "streambuf", "istream", "ostream", "iostream", "filebuf",
                     "ifstream", "ofstream", "fstream", "stringbuf", "istringstream",
                     "ostringstream", "stringstream", "syncbuf", "osyncstream"):
            for char, prefix in (("char", ""), ("wchar_t", "w")):
                with self.subTest(kind=kind, char=char):
                    self.assertEqual(shorten_common_types(
                        f"std::basic_{kind}<{char}, std::char_traits<{char}>>"),
                        f"std::{prefix}{kind}")
            # There are no standard u16ostream and similar aliases.
            text = f"std::basic_{kind}<char16_t>"
            self.assertEqual(shorten_common_types(text), text)

    def test_inline_namespaces_spacing_and_nested_containers(self):
        for namespace in ("std::", "std::__cxx11::", "std::__1::", "std::__2::", "std::__ndk1::"):
            with self.subTest(namespace=namespace):
                text = (f"std::vector<{namespace}basic_string< char, "
                        f"{namespace}char_traits< char >, {namespace}allocator<char> > >")
                self.assertEqual(shorten_common_types(text), "std::vector<std::string >")

    def test_preserves_overload_types_qualifiers_and_member_names(self):
        text = ("f(std::basic_string_view<char, std::char_traits<char>> const&, "
                "std::basic_string_view<wchar_t>*, std::basic_string<char>&&) const\n"
                "std::basic_string_view<char>::find+0x20\n")
        self.assertEqual(shorten_common_types(text),
                         "f(std::string_view const&, std::wstring_view*, std::string&&) const\n"
                         "std::string_view::find+0x20\n")

    def test_preserves_custom_or_mismatched_arguments(self):
        for text in (
            "std::basic_string<char, CustomTraits, std::allocator<char>>",
            "std::basic_string<char, std::char_traits<char>, MyAllocator<char>>",
            "std::basic_string<char, std::char_traits<wchar_t>>",
            "std::basic_string<char, std::char_traits<char>, std::allocator<wchar_t>>",
            "std::basic_string_view<char, MyTraits>",
            "std::basic_string_view<char, std::char_traits<char>, Extra>",
            "std::basic_string_view<unsigned char>",
            "std::basic_string<char, std::allocator<char>>",
            "mystd::basic_string<char>", "other::std::basic_string<char>",
            "std::__custom::basic_string<char>",
            "std::basic_string<char const>",
            "std::basic_string_view<char, std::char_traits<char>",
        ):
            with self.subTest(text=text):
                self.assertEqual(shorten_common_types(text), text)

    def test_leaves_numeric_aliases_and_line_boundaries_alone(self):
        text = "f(unsigned long, long, unsigned int, int)\nstd::basic_string<\nchar>\n"
        self.assertEqual(shorten_common_types(text), text)
        self.assertEqual(shorten_common_types(""), "")
        self.assertEqual(shorten_common_types("std::string_view"), "std::string_view")


if __name__ == "__main__":
    unittest.main()
