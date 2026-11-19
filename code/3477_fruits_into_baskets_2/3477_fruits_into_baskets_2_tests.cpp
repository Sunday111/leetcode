#include "3477_fruits_into_baskets_2.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numOfUnplacedFruits;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[3,6,1] [6,4,7] 0
)cases");

using t3477_fruits_into_baskets_2 = SolutionTests<Solution>;

TEST_P(t3477_fruits_into_baskets_2, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numOfUnplacedFruits(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3477_fruits_into_baskets_2,
    t3477_fruits_into_baskets_2::parameters(kCases.size()),
    t3477_fruits_into_baskets_2::name);
