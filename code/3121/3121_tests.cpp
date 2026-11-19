#include "3121.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numberOfSpecialChars;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"aaAbcBC"
3

"abc"
0

"AbBCab"
0


)");

using t3121 = SolutionTests<Solution>;

TEST_P(t3121, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numberOfSpecialChars(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3121,
    t3121::parameters(kCases.size()),
    t3121::name);
