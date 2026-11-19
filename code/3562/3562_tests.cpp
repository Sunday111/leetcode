#include "3562.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxProfit;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
2 [1,2] [4,3] [[1,2]] 3 5

2 [3,4] [5,8] [[1,2]] 4 4

3 [4,6,8] [7,9,11] [[1,2],[1,3]] 10 10

3 [5,2,3] [8,5,6] [[1,2],[2,3]] 7 12

3 [26,17,11] [40,46,13] [[1,3],[3,2]] 98 60

8 [39,14,15,30,25,16,46,11] [28,47,9,9,33,34,42,24] [[1,2],[2,7],[2,4],[7,6],[7,3],[3,5],[1,8]] 102 116

1 [28] [6] [] 2 0
)cases");

using t3562 = SolutionTests<Solution>;

TEST_P(t3562, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxProfit(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3562,
    t3562::parameters(kCases.size()),
    t3562::name);
