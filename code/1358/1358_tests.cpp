#include "1358.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numberOfSubstrings;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abcabc" 10
"aaacb"  3
"abc"    1
)");

using t1358 = SolutionTests<Solution>;

TEST_P(t1358, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numberOfSubstrings(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1358,
    t1358::parameters(kCases.size()),
    t1358::name);
