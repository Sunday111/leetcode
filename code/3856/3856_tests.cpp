#include "3856.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::trimTrailingVowels;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"idea"
"id"

"day"
"day"

"aeiou"
""


)");

using t3856 = SolutionTests<Solution>;

TEST_P(t3856, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.trimTrailingVowels(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3856,
    t3856::parameters(kCases.size()),
    t3856::name);
