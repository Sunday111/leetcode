#include "3700.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::zigZagArrays;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
3
4
5
2

3
1
3
10

1000000000
1
75
16
)");

using t3700 = SolutionTests<Solution>;

TEST_P(t3700, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.zigZagArrays(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3700,
    t3700::parameters(kCases.size()),
    t3700::name);
