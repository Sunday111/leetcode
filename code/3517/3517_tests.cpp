#include "3517.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::smallestPalindrome;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"z"
"z"

"babab"
"abbba"

"daccad"
"acddca"


)");

using t3517 = SolutionTests<Solution>;

TEST_P(t3517, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.smallestPalindrome(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3517,
    t3517::parameters(kCases.size()),
    t3517::name);
