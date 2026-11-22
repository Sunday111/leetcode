#include "2124.hpp"
#include "2124_2.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::checkString;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"aaabbb" true
"abab"   false
"bbb"    true
"a"      true
"b"      true
"ab"     true
"ba"     false
"aba"    false
"bba"    false
"aaabba" false
)");

using t2124 = SolutionTests<Solution, Solution_2>;

TEST_P(t2124, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.checkString(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2124,
    t2124::parameters(kCases.size()),
    t2124::name);
