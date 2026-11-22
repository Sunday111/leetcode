#!/usr/bin/env python3
"""Compare one function's assembly from two sources using matching build settings."""

import argparse
import difflib
from pathlib import Path
import shutil
import subprocess
import sys

from print_assembly import (
    add_assembly_options, color_enabled, read_function, render_function, write_output,
)
from assembly_types import shorten_common_types


def write_difference(difference: str, *, color="auto", side_by_side=True) -> None:
    delta = shutil.which("delta") if side_by_side and color_enabled(color) else None
    if delta:
        result = subprocess.run([delta, "--side-by-side"], input=difference, text=True)
        if result.returncode:
            raise ValueError(f"delta exited with status {result.returncode}")
    else:
        write_output(difference, color=color, language="diff")


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__,
        epilog="Exit status: 0 = identical displayed bodies, 1 = differences, "
               "2 = error. Compares the selected function, not its callees or "
               "referenced constant pools.")
    parser.add_argument("function", nargs="?", help="qualified C++ name; "
                        "for .s inputs, an exact mangled symbol")
    parser.add_argument("left", type=Path, help="first C++ source/header or .s file")
    parser.add_argument("right", type=Path, help="second C++ source/header or .s file")
    parser.add_argument("--side-by-side", action=argparse.BooleanOptionalAction, default=True,
                        help="show terminal diffs with delta --side-by-side when installed "
                             "(enabled by default)")
    add_assembly_options(parser)
    args = parser.parse_args(argv)
    if bool(args.function) == bool(args.address):
        parser.error("provide either FUNCTION or --address")
    if args.address and any(p.suffix == ".s" for p in (args.left, args.right)):
        parser.error(".s input requires a mangled FUNCTION symbol")
    try:
        bodies = []
        for source in (args.left, args.right):
            assembly, symbol = read_function(source, args)
            bodies.append(render_function(assembly, symbol, args))
        displayed = ([shorten_common_types(body) for body in bodies]
                     if args.demangle and args.filter_types else bodies)
        if bodies[0] == bodies[1]:
            write_output(displayed[0], color=args.color)
            return 0
        # Alias shortening can hide ABI distinctions, e.g. old vs new string.
        # Keep any distinct full lines that would otherwise share a spelling.
        spellings = {}
        for body, shown in zip(bodies, displayed):
            for full, short in zip(body.splitlines(keepends=True), shown.splitlines(keepends=True)):
                spellings.setdefault(short, set()).add(full)
        displayed = ["".join(full if len(spellings[short]) > 1 else short
                             for full, short in zip(body.splitlines(keepends=True),
                                                    shown.splitlines(keepends=True)))
                     for body, shown in zip(bodies, displayed)]
        difference = "".join(difflib.unified_diff(
            displayed[0].splitlines(keepends=True),
            displayed[1].splitlines(keepends=True),
            fromfile=str(args.left), tofile=str(args.right)))
        write_difference(difference, color=args.color, side_by_side=args.side_by_side)
        return 1
    except (OSError, ValueError) as error:
        print(f"{parser.prog}: {error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
