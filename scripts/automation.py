#!/usr/bin/python3

from pathlib import Path
import shutil
import argparse
import re
import json
import leetcode_fetch

SCRIPTS_DIR = Path(__file__).parent.resolve()
ROOT_DIR = SCRIPTS_DIR.parent
CODE_DIR = ROOT_DIR / 'code'


def read_file(p:Path) -> str:
    with open(file=p, mode='rt', encoding='utf-8') as file:
        return file.read()


def write_file(p:Path, data:str):
    with open(file=p, mode='wt', encoding='utf-8') as file:
        file.write(data)


def patch_text(text:str, variables:dict[str, str]) -> str:
    for k, v in variables.items():
        text = text.replace(k, v)
    return text


def patch_file(src:Path, dst_dir:Path, variables:dict[str, str]):
    file_data = patch_text(read_file(src), variables)
    dst_path = dst_dir / patch_text(src.name, variables)
    dst_dir.mkdir(parents=True, exist_ok=True)
    write_file(dst_path, file_data)


def create_project(name:str, override:bool, template_dir: Path):
    project_root = CODE_DIR / name

    if not override and project_root.exists() and any(project_root.iterdir()):
        raise RuntimeError(f'{project_root} exists and not empty')

    shutil.rmtree(project_root, ignore_errors=True)

    variables = {
        "____problem_name____": name
    }
    for src_path in template_dir.rglob("*"):
        if src_path.is_file():
            dst_dir = (project_root / src_path.relative_to(template_dir)).parent.resolve()
            patch_file(src_path, dst_dir, variables)

    project_root = project_root.resolve()
    header_path = (project_root / f"{name}.hpp").resolve()

    # Write structured metadata JSON that the editor-side script will read.
    meta = {
        "path_to_solution_header": str(header_path)
    }
    write_file(project_root / "metadata.json", json.dumps(meta, indent=2))

    # Return the project directory path (script prints this to stdout for the editor)
    return project_root


def create_leetcode_project(project_dir_name: str, problem_name_raw: str, override: bool, template_dir: Path):
    """
    project_dir_name: name of folder to create (normalized)
    problem_name_raw: original problem title provided by user (used for slugging/fetch)
    """
    project_root = CODE_DIR / project_dir_name

    if override:
        shutil.rmtree(project_root, ignore_errors=True)
    else:
        if project_root.exists() and any(project_root.iterdir()):
            raise FileExistsError(f"project already exists: {project_root}")

    project_root.mkdir(parents=True, exist_ok=True)

    header_name = f"{project_dir_name}.hpp"
    header_path = (project_root / header_name).resolve()

    # Try fetching using the raw problem name first, then try stripping a leading numeric id like "3630. "
    slug = leetcode_fetch.title_to_slug(problem_name_raw)
    info = leetcode_fetch.fetch_cpp_template(slug)

    variables = {"____problem_name____": project_dir_name}
    for src_path in template_dir.rglob("*"):
        if src_path.is_file():
            dst_dir = (project_root / src_path.relative_to(template_dir)).parent.resolve()
            patch_file(src_path, dst_dir, variables)

    if info:
        header_path.write_text(info)

    meta = {"path_to_solution_header": str(header_path)}
    write_file(project_root / "metadata.json", json.dumps(meta, indent=2))

    return project_root


def update_projects_list():
    projects_list_file = CODE_DIR / 'CMakeLists.txt'
    projects_list_file.unlink(missing_ok=True)

    with open(file=projects_list_file, mode='wt', encoding='utf-8') as f:
        f.write('cmake_minimum_required(VERSION 3.25)\n\n')
        for path in sorted(CODE_DIR.glob('*')):
            if path.is_dir():
                f.write(f'add_subdirectory({path.name})\n')


def embed_includes(target_file_path: Path):
    templates_dir = ROOT_DIR / "templates"
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


def normalize_name(name: str) -> str:
    """
    Normalize project name: lowercase, remove non-alnum/space, collapse spaces -> underscore.
    """
    name = name.lower()
    name = re.sub(r'[^0-9a-zA-Z\s]', '', name)
    name = re.sub(r'\s+', '_', name).strip('_')
    return name


def main():
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(dest='command')

    create_solution = subparsers.add_parser('create')
    create_solution.add_argument("--name", type=str, required=True)
    create_solution.add_argument("--override", type=bool, required=False, default=False)

    create_leetcode = subparsers.add_parser('create_leetcode')
    create_leetcode.add_argument("--name", type=str, required=True)
    create_leetcode.add_argument("--override", type=bool, required=False, default=False)

    update_projects_list_parser = subparsers.add_parser('update_projects_list')

    embed_includes_parser = subparsers.add_parser('embed_includes')
    embed_includes_parser.add_argument("path", type=Path)

    args = parser.parse_args()
    command:str = args.command
    match command:
        case 'create':
            project_dir = create_project(args.name, args.override, template_dir=SCRIPTS_DIR / 'solution_template')
            update_projects_list()
        case 'create_leetcode':
            norm_name = normalize_name(args.name)
            # pass raw problem name for fetching, use normalized folder name for filesystem
            project_dir = create_leetcode_project(norm_name, args.name, args.override, template_dir=SCRIPTS_DIR / 'solution_template2')
            print(str(project_dir))
            update_projects_list()
        case 'update_projects_list':
            update_projects_list()
        case 'embed_includes':
            embed_includes(args.path.resolve())


if __name__ == '__main__':
    main()
