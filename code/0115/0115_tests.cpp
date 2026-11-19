#include "0115.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numDistinct;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"rabbbit"   "rabbit"  3
"babgbag"   "bag"     5
)");

using t0115 = SolutionTests<Solution>;

TEST_P(t0115, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numDistinct(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0115,
    t0115::parameters(kCases.size()),
    t0115::name);
