#include "3882.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minCost;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2],[3,4]]
6

[[6,7],[5,8]]
9

[[2,7,5]]
0

[[1023]]
1023

[[1],[2],[4],[8]]
15

[[0,0,0],[0,0,0]]
0

[[1023,1023],[1023,1023]]
1023

[[31,32],[63,64]]
96

[[64,128],[256,512]]
704

[[1,3],[2,3]]
0

)");

using t3882 = SolutionTests<Solution>;

TEST_P(t3882, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minCost(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3882,
    t3882::parameters(kCases.size()),
    t3882::name);
