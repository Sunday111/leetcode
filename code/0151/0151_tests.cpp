#include "0151.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::reverseWords;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"the sky is blue"       "blue is sky the"
"  hello world  "       "world hello"
"a good   example"      "example good a"
)");

using t0151 = SolutionTests<Solution>;

TEST_P(t0151, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.reverseWords(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0151,
    t0151::parameters(kCases.size()),
    t0151::name);
