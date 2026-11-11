import contextlib
import io
import json
from pathlib import Path
import tempfile
import unittest
import sys
from unittest.mock import patch

import automation


class EmbedIncludesTests(unittest.TestCase):
    def embed(self, files):
        with tempfile.TemporaryDirectory(prefix="leetcode-embed-") as directory:
            root = Path(directory)
            for name, content in files.items():
                path = root / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(content, encoding="utf-8")
            with patch.object(automation, "ROOT_DIR", root):
                with contextlib.redirect_stderr(io.StringIO()):
                    result = automation.embed_includes(root / "solution.hpp")
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
                                    get_cpp_template=lambda *_: "class Solution { public: int next(int x) { return x + 1; } };"):
                    project = automation.create_leetcode_project(
                        {}, 42, False, automation.SCRIPTS_DIR / "leetcode_solution_template")
            self.assertEqual([p.name for p in project.glob("*tests.cpp")], ["0042_tests.cpp"])
            self.assertEqual(list(project.glob("*_test_cases.hpp")), [])
            tests = (project / "0042_tests.cpp").read_text()
            self.assertIn('#include "0042.hpp"', tests)
            self.assertIn("&Solution::next", tests)
            self.assertIn("1\n2\n\n2\n3", tests)
            self.assertIn("TEST_P(t0042, Test)", tests)
            self.assertNotIn("____", tests)
            metadata = json.loads((project / "0042.json").read_text())
            self.assertEqual(metadata["path_to_solution_header"], "0042.hpp")

    def test_generic_project_still_has_one_test_file(self):
        with tempfile.TemporaryDirectory(prefix="leetcode-create-") as directory:
            with patch.object(automation, "CODE_DIR", Path(directory)):
                project = automation.create_project(
                    "example", False, automation.SCRIPTS_DIR / "solution_template")
            self.assertEqual([p.name for p in project.glob("*tests.cpp")], ["example_tests.cpp"])
            self.assertEqual(list(project.glob("*_test_cases.hpp")), [])


if __name__ == "__main__":
    unittest.main()
