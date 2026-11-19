#include "3474.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::generateString;

inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"TFTF"
"ab"
"ababa"

"TFTF"
"abc"
""

"F"
"d"
"a"

"FT"
"wvxyy"
"awvxyy"

"TTFFT"
"fff"
""

"FFFF"
"ddb"
"aaaaaa"

"FFTFFF"
"a"
"bbabbb"

"FTFTFFTFFFTFFFF"
"vyv"
"avyvyvvyvavyvaaaa"

"FTFTFFTFFFTFFFF"
"vyv"
"avyvyvvyvavyvaaaa"
)");

using t3474 = SolutionTests<Solution>;

TEST_P(t3474, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.generateString(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3474,
    t3474::parameters(kCases.size()),
    t3474::name);
