#include "1967.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numOfStrings;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
["a","abc","bc","d"] "abc"          3
["a","b","c"]        "aaaaabbbbb"   2
["a","a","a"]        "ab"           3
)");

using t1967 = SolutionTests<Solution>;

TEST_P(t1967, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numOfStrings(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1967,
    t1967::parameters(kCases.size()),
    t1967::name);
