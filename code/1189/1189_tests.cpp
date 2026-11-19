#include "1189.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxNumberOfBalloons;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"nlaebolko"
1
"loonbalxballpoon"
2
"leetcode"
0
)");

using t1189 = SolutionTests<Solution>;

TEST_P(t1189, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxNumberOfBalloons(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1189,
    t1189::parameters(kCases.size()),
    t1189::name);
