#include "3870.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::countCommas;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
1002
3

998
0


)");

using t3870 = SolutionTests<Solution>;

TEST_P(t3870, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countCommas(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3870,
    t3870::parameters(kCases.size()),
    t3870::name);
