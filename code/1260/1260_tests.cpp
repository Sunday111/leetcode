#include "1260.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::shiftGrid;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2,3],[4,5,6],[7,8,9]]
1
[[9,1,2],[3,4,5],[6,7,8]]

[[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]]
4
[[12,0,21,13],[3,8,1,9],[19,7,2,5],[4,6,11,10]]

[[1,2,3],[4,5,6],[7,8,9]]
9
[[1,2,3],[4,5,6],[7,8,9]]
)");

using t1260 = SolutionTests<Solution>;

TEST_P(t1260, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.shiftGrid(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1260,
    t1260::parameters(kCases.size()),
    t1260::name);
