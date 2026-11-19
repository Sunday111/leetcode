#include "3120.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numberOfSpecialChars;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"aaAbcBC"
3

"abc"
0


)");

using t3120 = SolutionTests<Solution>;

TEST_P(t3120, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numberOfSpecialChars(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3120,
    t3120::parameters(kCases.size()),
    t3120::name);
