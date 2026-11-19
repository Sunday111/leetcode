#include "1074.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numSubmatrixSumTarget;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,1,0],[1,1,1],[0,1,0]]
0
4

[[1,-1],[-1,1]]
0
5

[[904]]
0
0
)");

using t1074 = SolutionTests<Solution>;

TEST_P(t1074, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numSubmatrixSumTarget(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1074,
    t1074::parameters(kCases.size()),
    t1074::name);
