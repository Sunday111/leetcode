#include "3796.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findMaxVal;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
10
[[3,1],[8,1]]
[2,2,3,1,4,5,1,1,2]
6

8
[[3,2]]
[3,5,2,4,2,3,1]
12


)");

using t3796 = SolutionTests<Solution>;

TEST_P(t3796, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findMaxVal(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3796,
    t3796::parameters(kCases.size()),
    t3796::name);
