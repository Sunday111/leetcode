#include "2563_count_the_number_of_fair_pairs.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countFairPairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0,1,7,4,4,5] 3 6 6
)cases");

using t2563_count_the_number_of_fair_pairs = SolutionTests<Solution>;

TEST_P(t2563_count_the_number_of_fair_pairs, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countFairPairs(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2563_count_the_number_of_fair_pairs,
    t2563_count_the_number_of_fair_pairs::parameters(kCases.size()),
    t2563_count_the_number_of_fair_pairs::name);
