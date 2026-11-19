#include "2761.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findPrimePairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
10 [[3,7],[5,5]]

2 []

100 [[3,97],[11,89],[17,83],[29,71],[41,59],[47,53]]
)cases");

using t2761_prime_pairs_with_target_sum = SolutionTests<Solution>;

TEST_P(t2761_prime_pairs_with_target_sum, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findPrimePairs(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2761_prime_pairs_with_target_sum,
    t2761_prime_pairs_with_target_sum::parameters(kCases.size()),
    t2761_prime_pairs_with_target_sum::name);
