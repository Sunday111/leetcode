"""Shorten standard aliases and default template arguments in demangled output."""

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
_VECTOR = re.compile(rf"(?<![\w:]){_STD}vector\s*<")
_ALLOCATOR = re.compile(rf"{_STD}allocator\s*<")


def _template_arguments(text: str, opening: int):
    """Read balanced arguments without splitting nested types or expressions."""
    stack = ["<"]
    pairs = {">": "<", ")": "(", "]": "[", "}": "{"}
    arguments = []
    start = opening + 1
    quote = None
    escaped = False
    for i in range(start, len(text)):
        char = text[i]
        if quote:
            if escaped:
                escaped = False
            elif char == "\\":
                escaped = True
            elif char == quote:
                quote = None
            continue
        if char in "\"'":
            quote = char
        elif char in "([{":
            stack.append(char)
        elif char == "<" and stack[-1] == "<":
            stack.append(char)
        elif char in pairs:
            if char == ">" and stack[-1] != "<":
                continue
            if stack[-1] != pairs[char]:
                return None
            stack.pop()
            if not stack:
                arguments.append(text[start:i].strip())
                return i + 1, arguments
        elif char == "," and stack == ["<"]:
            arguments.append(text[start:i].strip())
            start = i + 1
    return None


def _shorten_vectors(line: str) -> str:
    # Work inside out, including vectors nested in allocator arguments.
    for match in reversed(list(_VECTOR.finditer(line))):
        parsed = _template_arguments(line, match.end() - 1)
        if parsed is None or len(parsed[1]) != 2:
            continue
        end, (element, allocator) = parsed
        allocation = _ALLOCATOR.match(allocator)
        if allocation is None:
            continue
        allocated = _template_arguments(allocator, allocation.end() - 1)
        if allocated is None or allocated[0] != len(allocator) or len(allocated[1]) != 1:
            continue
        # Ignore spacing, but preserve token boundaries (e.g. unsigned int).
        if not element or re.findall(r"\w+|[^\s]", element) != re.findall(r"\w+|[^\s]", allocated[1][0]):
            continue
        line = line[:match.start()] + f"std::vector<{element}>" + line[end:]
    return line


def shorten_common_types(text: str) -> str:
    """Use standard aliases and omit vector's matching default allocator.

    Custom traits/allocators and cv/ref qualifiers retain their spelling.
    Numeric aliases are deliberately excluded: their meanings depend on the ABI.
    This is a display operation, not a canonical representation for comparisons.
    """
    lines = text.splitlines(keepends=True)
    for kind, pattern in _ALIASES:
        lines = [pattern.sub(lambda m: f"std::{_CHAR_PREFIX[m['char']]}{kind}", line)
                 for line in lines]
    return "".join(_shorten_vectors(line) for line in lines)
