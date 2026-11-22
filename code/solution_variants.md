# Multiple solutions for one problem

- Keep the default in `<id>.hpp` and alternatives in `<id>_<variant>.hpp`.
- Use `#pragma once`, include `solution_name.hpp`, and declare the class with
  a descriptive suffix:

  ```cpp
  class LC_SOLUTION_NAME(_radix)
  {
  public:
      // The problem's normal entry point.
  };
  ```

- Use `LC_SOLUTION_NAME()` for the default class, which expands to `Solution`.
  With `LC_LOCAL_BUILD`, `LC_SOLUTION_NAME(_radix)` expands to `Solution_radix`;
  otherwise it expands to the judge's `Solution`. The suffix is appended exactly
  as written, including its leading underscore. Each variant uses a different suffix.
- Include the headers normally in `<id>_tests.cpp`. Define one `kCases` table
  and use `SolutionTests` from `solution_tests.hpp`:

  ```cpp
  using t3041 = SolutionTests<Solution_adaptive, Solution_radix>;

  TEST_P(t3041, Test)
  {
      check(kCases, [](auto& solution, auto& nums)
            { return solution.maxSelectedElements(nums); });
  }

  INSTANTIATE_TEST_SUITE_P(
      Gen, t3041, t3041::parameters(kCases.size()), t3041::name);
  ```

  Every solution/case pair is a separate test, named with its class and case
  index, such as `Gen/t3041.Test/Solution_radix_C0`. The fixture copies inputs
  and creates a fresh solution instance for each invocation. Use distinct type
  names; namespace and template punctuation becomes underscores in test names.
  Generated projects start with `SolutionTests<Solution>`.
- For custom parsing, calls, or assertions, use
  `run(kCases, [](auto& solution, auto& inputs, auto& expected) { ... });`.
  The callback receives a fresh solution and copies of the case's inputs and
  expected result. Inputs can be any type, including raw text parsed inside the
  callback. `check` is the equality-checking convenience wrapper around `run`.
  [1980's tests](1980/1980_tests.cpp) demonstrate checking an answer's properties
  when several outputs are valid.
- Put shared problem-specific logic in a local helper header when useful.
  Embed any solution header with the existing `embed_includes` command to
  obtain an independent submission.

See [3041's tests](3041/3041_tests.cpp) for the complete pattern.
