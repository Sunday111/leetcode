# Template tests

This project mirrors the directory structure of `templates/`. Put tests for
`templates/path/to/file.hpp` in `templates_tests/path/to/file.cpp`. Keep
test-only helpers beside the tests that use them. When a header has multiple
test suites, give the additional files descriptive names in the same directory,
such as `bsv_count_dynamic.cpp` beside `bsv_count.cpp`.

The `test_utility/` directory covers the repository’s test infrastructure.
The `submission/` directory exercises headers in judge mode, in a separate
translation unit from their local-mode tests.

From the repository root, build and run the suite with:

```sh
cmake --build build --target lc_templates_tests
ctest --test-dir build/templates_tests --output-on-failure
```

To build this project independently, use a C++23 compiler and an installed
GoogleTest CMake package:

```sh
cmake -S templates_tests -B build-templates-tests
cmake --build build-templates-tests
ctest --test-dir build-templates-tests --output-on-failure
```
