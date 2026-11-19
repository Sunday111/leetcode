#include "3510_minimum_pair_removal_to_sort_array_ii.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumPairRemoval;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[5,2,3,1] 2

[1,2,2] 0

[1,1,4,1] 2

[1,1,4,4,2,-4,-1] 5

[3,6,-9,6,3,-4] 4
)cases");

using t3510_minimum_pair_removal_to_sort_array_ii = SolutionTests<Solution>;

TEST_P(t3510_minimum_pair_removal_to_sort_array_ii, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumPairRemoval(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3510_minimum_pair_removal_to_sort_array_ii,
    t3510_minimum_pair_removal_to_sort_array_ii::parameters(kCases.size()),
    t3510_minimum_pair_removal_to_sort_array_ii::name);
