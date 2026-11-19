#include "1402.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxSatisfaction;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[-1,-8,0,5,-7]
14
[4,3,2]
20
[-1,-4,-5]
0
)");

using t1402 = SolutionTests<Solution>;

TEST_P(t1402, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxSatisfaction(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1402,
    t1402::parameters(kCases.size()),
    t1402::name);
