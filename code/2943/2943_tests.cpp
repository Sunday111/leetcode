#include "2943.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maximizeSquareHoleArea;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
2 1 [2,3] [2] 4

1 1 [2] [2] 4

3 2 [3,2,4] [3,2] 9

4 40 [5,3,2,4] [36,41,6,34,33] 9
)cases");

using t2943 = SolutionTests<Solution>;

TEST_P(t2943, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximizeSquareHoleArea(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2943,
    t2943::parameters(kCases.size()),
    t2943::name);
