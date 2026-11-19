#include "0032.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::longestValidParentheses;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"(()"           2
")()())"        4
""              0
")()())()()("   4
)cases");

using t0032 = SolutionTests<Solution>;

TEST_P(t0032, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.longestValidParentheses(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0032,
    t0032::parameters(kCases.size()),
    t0032::name);
