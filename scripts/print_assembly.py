#!/usr/bin/env python3
"""Compile a C++ function and print its body from Clang/GCC ELF assembly."""

import argparse
import json
from pathlib import Path
import re
import subprocess
import sys
import tempfile


ROOT_DIR = Path(__file__).resolve().parent.parent
TARGET = "assembly_target"
SYMBOL = r"[A-Za-z_.$][\w.$]*"


def resolve_alias(assembly: str, symbol: str) -> str:
    aliases = dict(re.findall(
        rf"^\s*\.set\s+({SYMBOL})\s*,\s*({SYMBOL})\s*(?:#.*)?$",
        assembly, re.MULTILINE))
    seen = set()
    while symbol in aliases:
        if symbol in seen:
            raise ValueError(f"Cyclic assembly alias: {symbol}")
        seen.add(symbol)
        symbol = aliases[symbol]
    return symbol


def symbol_body(assembly: str, symbol: str) -> str:
    symbol = resolve_alias(assembly, symbol)
    label = re.search(rf"^{re.escape(symbol)}:\s*(?:[#;].*)?$",
                      assembly, re.MULTILINE)
    if label is None:
        raise ValueError(f"No emitted label for {symbol}")
    end = re.search(rf"^\s*\.size\s+{re.escape(symbol)}\s*,[^\n]*$",
                    assembly[label.end():], re.MULTILINE)
    if end is None:
        raise ValueError(f"No ELF .size directive for {symbol}")
    stop = label.end() + end.end()
    cfi_end = re.match(r"\n[ \t]*\.cfi_endproc[^\n]*", assembly[stop:])
    if cfi_end:
        stop += cfi_end.end()
    return assembly[label.start():stop] + "\n"


def target_function(assembly: str) -> str:
    target = resolve_alias(assembly, TARGET)
    label = re.search(rf"^{re.escape(target)}:[^\n]*\n", assembly, re.MULTILINE)
    if label is None:
        raise ValueError(f"No emitted label for {target}")
    marker = assembly[label.end():]
    end = re.search(
        rf"^(?:{SYMBOL}:|[ \t]*\.(?:size|section|text|data|bss|type|globl|weak)\b)",
        marker, re.MULTILINE)
    if end:
        marker = marker[:end.start()]
    functions = set(re.findall(
        rf"^\s*\.type\s+({SYMBOL})\s*,\s*[@%]function\b",
        assembly, re.MULTILINE))
    references = re.findall(
        rf"^\s*\.(?:quad|long|xword)\s+({SYMBOL})(?:\s|$)",
        marker, re.MULTILINE)
    targets = {resolve_alias(assembly, name) for name in references}
    targets &= {resolve_alias(assembly, name) for name in functions}
    if len(targets) != 1:
        raise ValueError(
            "The address did not select one emitted function. "
            "Virtual member pointers are not supported; use a concrete wrapper.")
    return targets.pop()


def compile_assembly(source: Path, address: str, *, compiler="clang++",
                     opt="O2", asan=True, syntax="att", flags=()) -> str:
    source = source.resolve(strict=True)
    with tempfile.TemporaryDirectory(prefix="leetcode-assembly-", dir="/tmp") as tmp:
        unit = Path(tmp) / "inspect.cpp"
        output = Path(tmp) / "inspect.s"
        unit.write_text(
            f"#include {json.dumps(str(source))}\n"
            f'extern "C" {{ [[gnu::used]] auto {TARGET} = ({address}); }}\n',
            encoding="utf-8")
        command = [compiler, "-std=c++23", f"-{opt}", "-DLC_LOCAL_BUILD",
                   "-I", str(ROOT_DIR / "templates"), "-include", "iostream",
                   f"-masm={syntax}"]
        if asan:
            command.append("-fsanitize=address")
        command.extend(flags)
        command.extend(["-S", "-x", "c++", str(unit), "-o", str(output)])
        result = subprocess.run(command, capture_output=True, text=True)
        if result.returncode:
            raise ValueError(result.stderr.strip() or
                             f"Compiler exited with status {result.returncode}")
        if result.stderr:
            print(result.stderr, file=sys.stderr, end="")
        return output.read_text(encoding="utf-8")


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(
        description=__doc__,
        epilog="Example: %(prog)s code/3693/3693.hpp Solution::climbStairs "
               "--opt O3 --flag=-mtune=native")
    parser.add_argument("source", type=Path, help="C++ source/header or existing .s file")
    parser.add_argument("function", nargs="?",
                        help="qualified C++ name, including template arguments; "
                             "for .s input, an exact mangled symbol")
    parser.add_argument("--address", help="complete C++ function-pointer expression "
                        "instead of FUNCTION, e.g. a static_cast resolving an overload")
    parser.add_argument("--compiler", default="clang++")
    parser.add_argument("--opt", choices=("O0", "O1", "O2", "O3", "Os", "Oz"),
                        default="O2")
    parser.add_argument("--asan", action=argparse.BooleanOptionalAction, default=True)
    parser.add_argument("--syntax", choices=("att", "intel"), default="att")
    parser.add_argument("--flag", action="append", default=[], metavar="FLAG",
                        help="extra compiler flag; repeat as --flag=-mtune=native")
    parser.add_argument("--save-assembly", type=Path,
                        help="also save the complete translation unit assembly "
                             "for inspecting callees and constant pools")
    args = parser.parse_args(argv)
    if bool(args.function) == bool(args.address):
        parser.error("provide either FUNCTION or --address")
    if args.source.suffix == ".s" and args.address:
        parser.error(".s input requires a mangled FUNCTION symbol")
    if args.save_assembly and args.save_assembly.resolve() == args.source.resolve():
        parser.error("--save-assembly must not overwrite the input")
    try:
        if args.source.suffix == ".s":
            assembly = args.source.read_text(encoding="utf-8")
            symbol = args.function
        else:
            assembly = compile_assembly(
                args.source, args.address or f"&{args.function}",
                compiler=args.compiler, opt=args.opt, asan=args.asan,
                syntax=args.syntax, flags=args.flag)
            symbol = target_function(assembly)
        body = symbol_body(assembly, symbol)
        if args.save_assembly:
            args.save_assembly.write_text(assembly, encoding="utf-8")
        print(body, end="")
    except (OSError, ValueError) as error:
        print(f"{parser.prog}: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
