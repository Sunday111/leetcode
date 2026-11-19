#include "3418.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumAmount;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,1,-1],[1,-2,3],[2,-3,4]]
8

[[10,10,10],[10,10,10]]
40


)");

using t3418 = SolutionTests<Solution>;

TEST_P(t3418, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximumAmount(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3418,
    t3418::parameters(kCases.size()),
    t3418::name);
