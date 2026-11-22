"""Shorten exact standard-library type specializations in demangled output."""

import re


_STD = r"std::(?:(?:__cxx11|__1|__2|__ndk1)::)?"
_CHAR_PREFIX = {"char": "", "wchar_t": "w", "char8_t": "u8",
                "char16_t": "u16", "char32_t": "u32"}
_STREAMS = ("ios", "streambuf", "istream", "ostream", "iostream",
            "filebuf", "ifstream", "ofstream", "fstream",
            "stringbuf", "istringstream", "ostringstream", "stringstream",
            "syncbuf", "osyncstream")


def _alias_pattern(kind: str) -> re.Pattern:
    characters = "|".join(_CHAR_PREFIX if kind in ("string", "string_view")
                          else ("char", "wchar_t"))
    traits = _STD + r"char_traits\s*<\s*(?P=char)\s*>"
    allocator = _STD + r"allocator\s*<\s*(?P=char)\s*>"
    # An allocator is the third argument of basic_string, after char_traits.
    defaults = traits + (rf"(?:\s*,\s*{allocator})?" if kind == "string" else "")
    return re.compile(
        rf"(?<![\w:]){_STD}basic_{kind}\s*<\s*(?P<char>{characters})"
        rf"\s*(?:,\s*{defaults}\s*)?>")


_ALIASES = [(kind, _alias_pattern(kind)) for kind in
            ("string", "string_view", *_STREAMS)]


def shorten_common_types(text: str) -> str:
    """Use standard aliases only when all explicit arguments match defaults.

    Custom traits/allocators and cv/ref qualifiers retain their spelling.
    Numeric aliases are deliberately excluded: their meanings depend on the ABI.
    This is a display operation, not a canonical representation for comparisons.
    """
    lines = text.splitlines(keepends=True)
    for kind, pattern in _ALIASES:
        lines = [pattern.sub(lambda m: f"std::{_CHAR_PREFIX[m['char']]}{kind}", line)
                 for line in lines]
    return "".join(lines)
