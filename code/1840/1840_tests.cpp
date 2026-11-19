#include "1840.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxBuilding;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
5
[[2,1],[4,1]]
2

6
[]
5

10
[[5,3],[2,5],[7,4],[10,3]]
5

10
[[8,5],[9,0],[6,2],[4,0],[3,2],[10,0],[5,3],[7,3],[2,4]]
2
)");

using t1840 = SolutionTests<Solution>;

TEST_P(t1840, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxBuilding(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1840,
    t1840::parameters(kCases.size()),
    t1840::name);
