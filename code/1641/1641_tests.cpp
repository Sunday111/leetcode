#include "1641.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::countVowelStrings;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
1
5

2
15

33
66045

50
316251
)");

using t1641 = SolutionTests<Solution>;

TEST_P(t1641, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countVowelStrings(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1641,
    t1641::parameters(kCases.size()),
    t1641::name);
