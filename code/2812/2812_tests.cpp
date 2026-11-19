#include "2812.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumSafenessFactor;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,0,0],[0,0,0],[0,0,1]]                       0
[[0,0,1],[0,0,0],[0,0,0]]                       2
[[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]       2
)");

using t2812 = SolutionTests<Solution>;

TEST_P(t2812, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximumSafenessFactor(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2812,
    t2812::parameters(kCases.size()),
    t2812::name);
