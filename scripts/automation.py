#!/usr/bin/python3

from pathlib import Path
import shutil
import argparse

SCRIPTS_DIR = Path(__file__).parent.resolve()
ROOT_DIR = SCRIPTS_DIR.parent
TEMPLATE_DIR = SCRIPTS_DIR / 'solution_template'
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


def create_project(name:str, override:bool):
    project_root = CODE_DIR / name

    if override:
        shutil.rmtree(project_root, ignore_errors=True)
    else:
        assert not project_root.exists()

    variables = {
        "____problem_name____": name
    }
    for src_path in TEMPLATE_DIR.rglob("*"):
        if src_path.is_file():
            dst_dir = (project_root / src_path.relative_to(TEMPLATE_DIR)).parent.resolve()
            patch_file(src_path, dst_dir, variables)


def update_projects_list():
    projects_list_file = CODE_DIR / 'CMakeLists.txt'
    projects_list_file.unlink(missing_ok=True)

    with open(file=projects_list_file, mode='wt', encoding='utf-8') as f:
        f.write('cmake_minimum_required(VERSION 3.25)\n\n')
        for path in sorted(CODE_DIR.glob('*')):
            if path.is_dir():
                f.write(f'add_subdirectory({path.name})\n')


def main():
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(dest='command')

    create_parser = subparsers.add_parser('create')
    create_parser.add_argument("--name", type=str, required=True)
    create_parser.add_argument("--override", type=bool, required=False, default=False)

    update_projects_list_parser = subparsers.add_parser('update_projects_list')

    args = parser.parse_args()
    command:str = args.command
    match command:
        case 'create':
            create_project(args.name, args.override)
            update_projects_list()
        case 'update_projects_list':
            update_projects_list()


if __name__ == '__main__':
    main()
