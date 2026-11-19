#include "3751.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::totalWaviness;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
120
130
3

198
202
3

4848
4848
2


)");

using t3751 = SolutionTests<Solution>;

TEST_P(t3751, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.totalWaviness(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3751,
    t3751::parameters(kCases.size()),
    t3751::name);
