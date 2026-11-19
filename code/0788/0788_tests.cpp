#include "0788.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::rotatedDigits;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
10 4
1  0
2  1
)");

using t0788 = SolutionTests<Solution>;

TEST_P(t0788, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.rotatedDigits(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0788,
    t0788::parameters(kCases.size()),
    t0788::name);
