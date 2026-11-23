import subprocess


def preprocess_cpp(source: str) -> str:
    # Experimental: header-defined macros are unavailable, and compiler conditions
    # are resolved for the local Clang configuration rather than the judge's.
    return subprocess.run(
        ["clang++", "-E", "-P", "-CC", "-x", "c++", "-std=c++23",
         "-ULC_LOCAL_BUILD", "-"],
        input=source, text=True, stdout=subprocess.PIPE, check=True,
    ).stdout
