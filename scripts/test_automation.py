import contextlib
import io
from pathlib import Path
import tempfile
import unittest
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
                with contextlib.redirect_stdout(io.StringIO()):
                    automation.embed_includes(root / "solution.hpp")
            return (root / "solution_mono.hpp").read_text(encoding="utf-8")

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


if __name__ == "__main__":
    unittest.main()
