#include "3689.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxTotalValue;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,2]
2
4

[4,2,5,1]
3
12


)");

using t3689 = SolutionTests<Solution>;

TEST_P(t3689, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxTotalValue(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3689,
    t3689::parameters(kCases.size()),
    t3689::name);
