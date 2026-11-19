#include "3534.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

/*
 */

inline static constexpr auto kMethodToTest = &Solution::pathExistenceQueries;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(

5
[5,3,1,9,10]
2
[[0,1],[0,2],[2,3],[4,3]]
[1,2,-1,1]

5
[1,8,3,4,2]
3
[[0,3],[2,4]]
[1,1]

3
[3,6,1]
1
[[0,0],[0,1],[1,2]]
[0,-1,-1]

5
[18,14,8,18,0]
8
[[1,1],[4,0]]
[0,3]

5
[0,8,14,18,18]
8
[[4,0]]
[3]
)");

using t3534 = SolutionTests<Solution>;

TEST_P(t3534, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.pathExistenceQueries(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3534,
    t3534::parameters(kCases.size()),
    t3534::name);
