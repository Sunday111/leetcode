#include "3704_count_no_zero_pairs_that_sum_to_n.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countNoZeroPairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1000000000000000 50891681057058
)cases");

using t3704_count_no_zero_pairs_that_sum_to_n = SolutionTests<Solution>;

TEST_P(t3704_count_no_zero_pairs_that_sum_to_n, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countNoZeroPairs(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3704_count_no_zero_pairs_that_sum_to_n,
    t3704_count_no_zero_pairs_that_sum_to_n::parameters(kCases.size()),
    t3704_count_no_zero_pairs_that_sum_to_n::name);
