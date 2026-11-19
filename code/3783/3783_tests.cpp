#include "3783.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::mirrorDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
25
27

10
9

7
0


)");

using t3783 = SolutionTests<Solution>;

TEST_P(t3783, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.mirrorDistance(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3783,
    t3783::parameters(kCases.size()),
    t3783::name);
