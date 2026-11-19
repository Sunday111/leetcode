#include "1306.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::canReach;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[4,2,3,0,3,1,2]
5
true
[4,2,3,0,3,1,2]
0
true
[3,0,2,1,2]
2
false
)");

using t1306 = SolutionTests<Solution>;

TEST_P(t1306, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.canReach(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1306,
    t1306::parameters(kCases.size()),
    t1306::name);
