import contextlib
import io
import json
from pathlib import Path
import tempfile
import subprocess
import unittest
import sys
from unittest.mock import patch

import automation


class EmbedIncludesTests(unittest.TestCase):
    def embed(self, files, **options):
        with tempfile.TemporaryDirectory(prefix="leetcode-embed-") as directory:
            root = Path(directory)
            for name, content in files.items():
                path = root / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(content, encoding="utf-8")
            with patch.object(automation, "ROOT_DIR", root):
                with contextlib.redirect_stderr(io.StringIO()):
                    result = automation.embed_includes(root / "solution.hpp", **options)
            self.assertEqual({str(p.relative_to(root)) for p in root.rglob("*")
                              if p.is_file()}, set(files))
            return result

    def test_cli_separates_source_from_diagnostics(self):
        with tempfile.TemporaryDirectory(prefix="leetcode-embed-") as directory:
            source = Path(directory) / "solution.hpp"
            source.write_text('#include <vector>\n\nint answer = 42;\n')
            stdout, stderr = io.StringIO(), io.StringIO()
            with patch.object(sys, "argv", ["automation.py", "embed_includes", str(source)]):
                with contextlib.redirect_stdout(stdout), contextlib.redirect_stderr(stderr):
                    automation.main()
            self.assertEqual(stdout.getvalue(), '#include <vector>\n\n\nint answer = 42;\n')
            self.assertIn("vector: embed", stderr.getvalue())
            self.assertEqual(list(Path(directory).iterdir()), [source])

    def test_preprocessing_is_opt_in(self):
        source = "#define VALUE 42\nint answer = VALUE;\n"
        result = self.embed({"solution.hpp": source})
        self.assertIn(source, result)

    def test_preprocesses_embedded_macros_before_restoring_external_includes(self):
        result = self.embed({
            "solution.hpp": '#include <vector>\n#include "local.hpp"\n#include "external.hpp"\n'
                            'class LC_SOLUTION_NAME(_2) { std::vector<int> data; };\n'
                            'int JOIN(an, swer) = VALUE;\n'
                            '// VALUE stays in comments\n'
                            'const char* text = "VALUE";\n',
            "local.hpp": '#pragma once\n#include "values.hpp"\n'
                         '#ifdef LC_LOCAL_BUILD\n#error local build selected\n#else\n'
                         '#define LC_SOLUTION_NAME(suffix) Solution\n#endif\n'
                         '#define JOIN(a, b) a##b\n',
            "values.hpp": '#define VALUE (20 + \\\n22)\n',
        }, preprocess=True)
        self.assertTrue(result.startswith('#include "external.hpp"\n#include <vector>\n'))
        self.assertIn('class Solution { std::vector<int> data; };', result)
        self.assertIn('int answer = (20 + 22);', result)
        self.assertIn('// VALUE stays in comments', result)
        self.assertIn('"VALUE"', result)
        for directive in ('#define', '#ifdef', '#else', '#endif', '#pragma once'):
            self.assertNotIn(directive, result)

    def test_cli_preprocessing_and_errors(self):
        with tempfile.TemporaryDirectory(prefix="leetcode-preprocess-") as directory:
            source = Path(directory) / "solution.hpp"
            source.write_text('#include <vector>\n#define VALUE 42\nint answer = VALUE;\n')
            args = [sys.executable, str(automation.SCRIPTS_DIR / "automation.py"),
                    "embed_includes", str(source), "--preprocess"]
            result = subprocess.run(args, text=True, capture_output=True)
            self.assertEqual(result.returncode, 0, result.stderr)
            self.assertIn('#include <vector>\n', result.stdout)
            self.assertIn('int answer = 42;', result.stdout)
            self.assertNotIn('#define', result.stdout)
            source.write_text('#include <vector>\n#error preprocessing failed\n')
            result = subprocess.run(args, text=True, capture_output=True)
            self.assertNotEqual(result.returncode, 0)
            self.assertEqual(result.stdout, '')
            self.assertIn('preprocessing failed', result.stderr)
            self.assertEqual(list(Path(directory).iterdir()), [source])

    def test_nested_relative_headers_precede_template_root(self):
        result = self.embed({
            "solution.hpp": '#include "tree/make.hpp"\nvoid solution();\n',
            "templates/tree/make.hpp": '#pragma once\n#include "tree.hpp"\nvoid make();\n',
            "templates/tree/tree.hpp": '#pragma once\n#include "../types.hpp"\nstruct Tree {};\n',
            "templates/types.hpp": "using Index = unsigned;\n",
            "templates/tree.hpp": "wrong header\n",
        })
        self.assertEqual(result.strip(),
                         "using Index = unsigned;\nstruct Tree {};\nvoid make();\nvoid solution();")

    def test_same_basename_in_different_directories_and_duplicate_paths(self):
        result = self.embed({
            "solution.hpp": '#include "a/make.hpp"\n#include "b/make.hpp"\n#include "a/item.hpp"\n',
            "templates/a/make.hpp": '#include "item.hpp"\n#include "../a/item.hpp"\n',
            "templates/a/item.hpp": "struct A {};\n",
            "templates/b/make.hpp": '#include "item.hpp"\n',
            "templates/b/item.hpp": "struct B {};\n",
        })
        self.assertEqual(result.strip(), "struct A {};\nstruct B {};")

    def test_source_relative_headers_template_fallback_and_system_includes(self):
        result = self.embed({
            "solution.hpp": '#include "local.hpp"\n#include <vector>\n',
            "local.hpp": '#include "shared.hpp"\n#include <vector>\n#include "external.hpp"\nvoid local();\n',
            "templates/shared.hpp": "struct Shared {};\n",
            "vector": "wrong header\n",
        })
        self.assertEqual(result.strip(),
                         '#include "external.hpp"\n#include <vector>\n\nstruct Shared {};\nvoid local();')


class CreateSolutionTests(unittest.TestCase):
    def test_leetcode_project_has_one_self_contained_test_file(self):
        with tempfile.TemporaryDirectory(prefix="leetcode-create-") as directory:
            with patch.object(automation, "CODE_DIR", Path(directory)):
                with patch.multiple(automation.leetcode_fetch,
                                    get_slug_by_number=lambda *_: "example",
                                    problem_details_by_slug=lambda *_: {"title": "Example"},
                                    get_sample_inputs=lambda *_: ["1", "2"],
                                    get_sample_outputs=lambda *_: ["2", "3"],
                                    get_method_name=lambda *_: "next",
                                    get_cpp_template=lambda *_: "class SolutionHelper {}; class Solution { public: int next(int x) { return x + 1; } };"):
                    project = automation.create_leetcode_project(
                        {}, 42, False, automation.SCRIPTS_DIR / "leetcode_solution_template")
            self.assertEqual([p.name for p in project.glob("*tests.cpp")], ["0042_tests.cpp"])
            self.assertEqual(list(project.glob("*_test_cases.hpp")), [])
            tests = (project / "0042_tests.cpp").read_text()
            self.assertIn('#include "0042.hpp"', tests)
            self.assertIn("&Solution::next", tests)
            self.assertIn("1\n2\n\n2\n3", tests)
            self.assertIn("TEST_P(t0042, Test)", tests)
            self.assertIn("using t0042 = SolutionTests<Solution>;", tests)
            self.assertIn("return solution.next(args...);", tests)
            self.assertIn("t0042::parameters(kCases.size())", tests)
            self.assertIn("t0042::name", tests)
            self.assertNotIn("____", tests)
            header = (project / "0042.hpp").read_text()
            self.assertIn('#include "solution_name.hpp"', header)
            self.assertIn("class LC_SOLUTION_NAME()", header)
            self.assertIn("class SolutionHelper", header)
            self.assertIn("int next(int x) { return x + 1; }", header)
            self.assertNotIn("class Solution {", header)
            metadata = json.loads((project / "0042.json").read_text())
            self.assertEqual(metadata["path_to_solution_header"], "0042.hpp")

    def test_leetcode_project_preserves_named_design_class(self):
        starter = "class ParkingSystem { public: explicit ParkingSystem(int) {} };"
        with tempfile.TemporaryDirectory(prefix="leetcode-create-") as directory:
            with patch.object(automation, "CODE_DIR", Path(directory)):
                with patch.multiple(automation.leetcode_fetch,
                                    get_slug_by_number=lambda *_: "design-parking-system",
                                    problem_details_by_slug=lambda *_: {"title": "Design Parking System"},
                                    get_sample_inputs=lambda *_: [],
                                    get_sample_outputs=lambda *_: [],
                                    get_method_name=lambda *_: "addCar",
                                    get_cpp_template=lambda *_: starter):
                    project = automation.create_leetcode_project(
                        {}, 1603, False, automation.SCRIPTS_DIR / "leetcode_solution_template")
            header = (project / "1603.hpp").read_text()
            self.assertIn(starter, header)
            self.assertNotIn("LC_SOLUTION_NAME", header)

    def test_generic_project_still_has_one_test_file(self):
        with tempfile.TemporaryDirectory(prefix="leetcode-create-") as directory:
            with patch.object(automation, "CODE_DIR", Path(directory)):
                project = automation.create_project(
                    "example", False, automation.SCRIPTS_DIR / "solution_template")
            self.assertEqual([p.name for p in project.glob("*tests.cpp")], ["example_tests.cpp"])
            self.assertEqual(list(project.glob("*_test_cases.hpp")), [])
            tests = (project / "example_tests.cpp").read_text()
            self.assertIn("using texample = SolutionTests<Solution>;", tests)
            self.assertIn("texample::parameters(kCases.size())", tests)
            self.assertIn("texample::name", tests)
            header = (project / "example.hpp").read_text()
            self.assertIn('#include "solution_name.hpp"', header)
            self.assertIn("class LC_SOLUTION_NAME()", header)


if __name__ == "__main__":
    unittest.main()
