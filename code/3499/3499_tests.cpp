#include "3499.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::maxActiveSectionsAfterTrade;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"01"
1

"0100"
4

"1000100"
7

"01010"
4


)");

using t3499 = SolutionTests<Solution>;

TEST_P(t3499, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxActiveSectionsAfterTrade(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3499,
    t3499::parameters(kCases.size()),
    t3499::name);
