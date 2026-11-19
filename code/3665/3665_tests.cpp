#include "3665.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::uniquePaths;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,1,0],[0,0,1],[1,0,0]]
5

[[0,0],[0,0]]
2

[[0,1,1],[1,1,0]]
1

[[0,0],[1,0],[0,0]]
2

[[0,0,0],[1,1,0],[0,0,0]]
3

[[0,0],[1,1],[0,1],[0,0]]
0

[[0,1,1,1],[1,1,1,1],[1,1,1,1],[1,1,1,0]]
2

[[0,0,0,0],[0,0,0,0],[0,0,0,0]]
10

)");

using t3665 = SolutionTests<Solution>;

TEST_P(t3665, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.uniquePaths(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3665,
    t3665::parameters(kCases.size()),
    t3665::name);
