#include "1081.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::smallestSubsequence;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"bcabc"     "abc"
"cbacdcbc"  "acdb"
)");

using t1081 = SolutionTests<Solution>;

TEST_P(t1081, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.smallestSubsequence(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1081,
    t1081::parameters(kCases.size()),
    t1081::name);
