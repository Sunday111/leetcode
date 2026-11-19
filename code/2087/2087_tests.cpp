#include "2087.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minCost;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,0]
[2,3]
[5,4,3]
[8,2,6,7]
18

[0,0]
[0,0]
[5]
[26]
0
)");

using t2087 = SolutionTests<Solution>;

TEST_P(t2087, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minCost(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2087,
    t2087::parameters(kCases.size()),
    t2087::name);
