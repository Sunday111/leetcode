from pathlib import Path
import sys

SCRIPT_DIR = Path(__file__).parent.resolve()
ROOT_DIR = SCRIPT_DIR.parent


def main():
    templates_dir = ROOT_DIR / "templates"
    target_file_path = Path(sys.argv[1]).resolve()
    if not (target_file_path.exists() and target_file_path.is_file()):
        raise FileNotFoundError()

    included: set[Path] = set()
    not_included: dict[str, str] = dict()

    src: list[str] = list()
    with open(file=target_file_path, mode="rt", encoding="utf-8") as target_file:
        for line in target_file:
            src.append(line.rstrip())

    result: list[str] = list()

    added_one = 1
    while added_one:
        added_one = False
        include = "#include "
        for line in src:
            if "#pragma once" in line:
                continue

            idx = line.find(include)

            if idx == -1 or added_one:
                result.append(line)
                continue

            part = line[idx + len(include) :].strip()
            assert len(part) > 2
            assert part[0] in '"<'
            assert part[-1] in '">'
            include_val = part[1:-1]
            include_path = (templates_dir / include_val).resolve()

            if include_path in included:
                print(f"{include_val}: skip")
                continue
            print(f"{include_val}: embed")

            if include_path.is_file():
                with open(file=include_path, mode="rt", encoding="utf-8") as included_file:
                    for included_line in included_file:
                        result.append(included_line.rstrip())

                included.add(include_path)
                added_one = True
            else:
                not_included[include_val] = part[0]

        src = result
        result = list()

    result_file_path = target_file_path.with_name(f"{target_file_path.stem}_mono{target_file_path.suffix}")

    mirror = {
        "<": ">",
        '"': '"',
    }
    with open(file=result_file_path, mode="wt", encoding="utf-8") as result_file:
        for val in sorted(not_included.keys()):
            c = not_included[val]
            result_file.write(f"#include {c}{val}{mirror[c]}\n")

        result_file.write("\n")

        for line in src:
            result_file.write(line)
            result_file.write("\n")


if __name__ == "__main__":
    main()
