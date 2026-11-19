#include "3363_find_the_maximum_number_of_fruits_collected.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxCollectedFruits;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]] 100
)cases");

using t3363_find_the_maximum_number_of_fruits_collected =
    SolutionTests<Solution>;

TEST_P(t3363_find_the_maximum_number_of_fruits_collected, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxCollectedFruits(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3363_find_the_maximum_number_of_fruits_collected,
    t3363_find_the_maximum_number_of_fruits_collected::parameters(
        kCases.size()),
    t3363_find_the_maximum_number_of_fruits_collected::name);
