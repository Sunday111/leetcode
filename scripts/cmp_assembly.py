#!/usr/bin/env python3
"""Compare two SOURCE:FUNCTION targets using matching build settings."""

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


def parse_target(value: str) -> tuple[Path, str]:
    source, separator, function = value.partition(":")
    if not separator or not source or not function.strip():
        raise argparse.ArgumentTypeError("expected SOURCE:FUNCTION, e.g. solution.hpp:Solution::solve")
    return Path(source), function.strip()


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
    parser.add_argument("left", type=parse_target, metavar="SOURCE:FUNCTION",
                        help="first source/header and qualified function; .s files use mangled symbols")
    parser.add_argument("right", type=parse_target, metavar="SOURCE:FUNCTION",
                        help="second source/header and qualified function; .s files use mangled symbols")
    parser.add_argument("--left-address", help="function-pointer expression resolving the left overload")
    parser.add_argument("--right-address", help="function-pointer expression resolving the right overload")
    parser.add_argument("--side-by-side", action=argparse.BooleanOptionalAction, default=True,
                        help="show terminal diffs with delta --side-by-side when installed "
                             "(enabled by default)")
    add_assembly_options(parser, include_address=False)
    args = parser.parse_args(argv)
    targets = ((args.left, args.left_address), (args.right, args.right_address))
    for (source, _), address in targets:
        if source.suffix == ".s" and address:
            parser.error(".s input requires a mangled FUNCTION symbol, not an address expression")
    try:
        bodies = []
        for (source, function), address in targets:
            selection = argparse.Namespace(**vars(args), function=function, address=address)
            assembly, symbol = read_function(source, selection)
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
            fromfile=f"{args.left[0]}:{args.left[1]}",
            tofile=f"{args.right[0]}:{args.right[1]}"))
        write_difference(difference, color=args.color, side_by_side=args.side_by_side)
        return 1
    except (OSError, ValueError) as error:
        print(f"{parser.prog}: {error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
