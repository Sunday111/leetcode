#include "0940.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::distinctSubseqII;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abc" 7
"aba" 6
"aaa" 3
)");

using t0940 = SolutionTests<Solution>;

TEST_P(t0940, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.distinctSubseqII(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0940,
    t0940::parameters(kCases.size()),
    t0940::name);
