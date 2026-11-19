#include "1594.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxProductPath;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]
-1

[[1,-2,1],[1,-2,1],[3,-4,1]]
8

[[1,3],[0,-4]]
0
)");

using t1594 = SolutionTests<Solution>;

TEST_P(t1594, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxProductPath(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1594,
    t1594::parameters(kCases.size()),
    t1594::name);
