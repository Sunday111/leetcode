#include "0856.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::scoreOfParentheses;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"()" 1
"(())" 2
"()()" 2
"(()(()))" 6
"((()))" 4
"(()())" 4
"(())()" 3
"()(())" 3
"(()())(())" 6
"((())())" 6
"((()()))" 8
"()()()()()()()()()()()()()()()()()()()()()()()()()" 25
"((((((((((((((((((((((((()))))))))))))))))))))))))" 16777216
)cases");

using t0856 = SolutionTests<Solution>;

TEST_P(t0856, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.scoreOfParentheses(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0856,
    t0856::parameters(kCases.size()),
    t0856::name);
