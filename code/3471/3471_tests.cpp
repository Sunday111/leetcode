#include "3471.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::largestInteger;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,9,2,1,7]
3
7

[3,9,7,2,1,7]
4
3

[0,0]
1
-1


)");

using t3471 = SolutionTests<Solution>;

TEST_P(t3471, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.largestInteger(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3471,
    t3471::parameters(kCases.size()),
    t3471::name);
