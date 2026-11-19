#include "3691.hpp"
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

using t3691 = SolutionTests<Solution>;

TEST_P(t3691, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxTotalValue(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3691,
    t3691::parameters(kCases.size()),
    t3691::name);
