#include <print>

#include "3446.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::sortMatrix;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,7,3],[9,8,2],[4,5,6]] [[8,2,3],[9,6,7],[4,5,1]]
)cases");

using t3446 = SolutionTests<Solution>;

TEST_P(t3446, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.sortMatrix(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3446,
    t3446::parameters(kCases.size()),
    t3446::name);
