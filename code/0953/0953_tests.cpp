#include "0953.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isAlienSorted;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["hello","leetcode"] "hlabcdefgijkmnopqrstuvwxyz" true
)cases");

using t0953 = SolutionTests<Solution>;

TEST_P(t0953, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.isAlienSorted(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0953,
    t0953::parameters(kCases.size()),
    t0953::name);
