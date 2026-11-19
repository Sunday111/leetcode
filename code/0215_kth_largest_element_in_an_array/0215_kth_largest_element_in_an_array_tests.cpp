#include "0215_kth_largest_element_in_an_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findKthLargest;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0,1,2,3,4,5,9999] 1 9999
)cases");

using t0215_kth_largest_element_in_an_array = SolutionTests<Solution>;

TEST_P(t0215_kth_largest_element_in_an_array, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findKthLargest(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0215_kth_largest_element_in_an_array,
    t0215_kth_largest_element_in_an_array::parameters(kCases.size()),
    t0215_kth_largest_element_in_an_array::name);
