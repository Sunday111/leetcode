#include "1584.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minCostConnectPoints;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,0],[2,2],[3,10],[5,2],[7,0]]    20
[[3,12],[-2,5],[-4,1]]              18
[[2,-3],[-17,-8],[13,8],[-17,-15]]  53
[[0,0]]                             0
)");

using t1584 = SolutionTests<Solution>;

TEST_P(t1584, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minCostConnectPoints(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1584,
    t1584::parameters(kCases.size()),
    t1584::name);
