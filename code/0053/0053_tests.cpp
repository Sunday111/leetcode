#include "0053.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, int>(R"cases(
[-2,1,-3,4,-1,2,1,-5,4] 6

[1] 1

[5,4,-1,7,8] 23
)cases");

using t0053 = SolutionTests<Solution>;

TEST_P(t0053, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxSubArray(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0053,
    t0053::parameters(kCases.size()),
    t0053::name);
