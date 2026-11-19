#include "0797_all_paths_from_source_to_target.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::allPathsSourceTarget;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2],[3],[3],[]] [[0,1,3],[0,2,3]]

[[4,3,1],[3,2,4],[3],[4],[]] [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]
)cases");

using t0797_all_paths_from_source_to_target = SolutionTests<Solution>;

TEST_P(t0797_all_paths_from_source_to_target, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.allPathsSourceTarget(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0797_all_paths_from_source_to_target,
    t0797_all_paths_from_source_to_target::parameters(kCases.size()),
    t0797_all_paths_from_source_to_target::name);
