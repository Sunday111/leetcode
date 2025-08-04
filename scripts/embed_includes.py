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

    num_embeds = 1
    while num_embeds != 0:
        num_embeds = 0
        include = "#include "
        for line in src:
            if "#pragma once" in line:
                continue

            idx = line.find(include)
            if idx != -1:
                part = line[idx + len(include) :].strip()
                assert len(part) > 2
                assert part[0] in '"<'
                assert part[-1] in '">'
                include_val = part[1:-1]
                include_path = (templates_dir / include_val).resolve()

                if include_path in included:
                    continue

                if include_path.is_file():
                    with open(file=include_path, mode="rt", encoding="utf-8") as included_file:
                        for included_line in included_file:
                            result.append(included_line.rstrip())

                    included.add(include_path)
                    num_embeds += 1
                else:
                    not_included[include_val] = part[0]

                continue

            result.append(line)

        src = result
        result = list()

    result_file_path = target_file_path.with_name(f"{target_file_path.stem}_mono.{target_file_path.suffix}")

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
