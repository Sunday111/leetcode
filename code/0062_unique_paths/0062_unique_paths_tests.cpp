#include "0062_unique_paths.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::uniquePaths;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 7 28

3 2 3
)cases");

using t0062_unique_paths = SolutionTests<Solution>;

TEST_P(t0062_unique_paths, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.uniquePaths(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0062_unique_paths,
    t0062_unique_paths::parameters(kCases.size()),
    t0062_unique_paths::name);
