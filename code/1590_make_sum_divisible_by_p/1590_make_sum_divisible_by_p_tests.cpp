#include "1590_make_sum_divisible_by_p.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minSubarray;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[3,1,4,2] 6 1
)cases");

using t1590_make_sum_divisible_by_p = SolutionTests<Solution>;

TEST_P(t1590_make_sum_divisible_by_p, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minSubarray(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1590_make_sum_divisible_by_p,
    t1590_make_sum_divisible_by_p::parameters(kCases.size()),
    t1590_make_sum_divisible_by_p::name);
