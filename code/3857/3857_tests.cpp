#include "3857.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minCost;

inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
3
3

4
6

500
124750
)");

using t3857 = SolutionTests<Solution>;

TEST_P(t3857, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minCost(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3857,
    t3857::parameters(kCases.size()),
    t3857::name);
