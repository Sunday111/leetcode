#include "0797.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::allPathsSourceTarget;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2],[3],[3],[]] [[0,1,3],[0,2,3]]

[[4,3,1],[3,2,4],[3],[4],[]] [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]
)cases");

using t0797 = SolutionTests<Solution>;

TEST_P(t0797, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.allPathsSourceTarget(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0797,
    t0797::parameters(kCases.size()),
    t0797::name);
