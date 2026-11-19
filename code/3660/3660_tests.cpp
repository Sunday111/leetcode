#include "3660.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxValue;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,1,3]
[2,2,3]

[2,3,1]
[3,3,3]


)");

using t3660 = SolutionTests<Solution>;

TEST_P(t3660, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxValue(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3660,
    t3660::parameters(kCases.size()),
    t3660::name);
