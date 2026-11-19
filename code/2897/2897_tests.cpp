#include "2897.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxSum;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,6,5,8]           2  261
[4,5,4,7]           3  90
)");

using t2897 = SolutionTests<Solution>;

TEST_P(t2897, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args) { return solution.maxSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2897,
    t2897::parameters(kCases.size()),
    t2897::name);
