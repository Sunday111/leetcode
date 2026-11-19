#include "1406.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::stoneGameIII;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3,7]       "Bob"
[1,2,3,-9]      "Alice"
[1,2,3,6]       "Tie"
[-1,-2,-3]      "Tie"
)");

using t1406 = SolutionTests<Solution>;

TEST_P(t1406, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.stoneGameIII(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1406,
    t1406::parameters(kCases.size()),
    t1406::name);
