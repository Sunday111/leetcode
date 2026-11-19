#include "0045.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, unsigned int>(
        R"cases(
[2,3,1,1,4] 2

[2,3,0,1,4] 2

[0] 0
)cases");

using t0045 = SolutionTests<Solution>;

TEST_P(t0045, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args) { return solution.jump(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0045,
    t0045::parameters(kCases.size()),
    t0045::name);
