#include "0835.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::largestOverlap;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,1,0],[0,1,0],[0,1,0]]
[[0,0,0],[0,1,1],[0,0,1]]
3
[[1]]
[[1]]
1
[[0]]
[[0]]
0
[[1,0,0,0],[0,0,0,0],[0,0,1,0],[0,0,0,0]]
[[0,0,0,0],[0,1,0,0],[0,0,0,0],[0,0,0,1]]
2
[[0,0,0,0],[0,0,0,0],[1,1,1,0],[0,0,0,0]]
[[0,1,1,1],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
3
)");

using t0835 = SolutionTests<Solution>;

TEST_P(t0835, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.largestOverlap(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0835,
    t0835::parameters(kCases.size()),
    t0835::name);
