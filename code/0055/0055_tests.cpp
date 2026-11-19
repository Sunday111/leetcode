#include "0055.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, unsigned int>(
        R"cases(
[2,3,1,1,4] 1

[3,2,1,0,4] 0
)cases");

using t0055 = SolutionTests<Solution>;

TEST_P(t0055, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.canJump(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0055,
    t0055::parameters(kCases.size()),
    t0055::name);
