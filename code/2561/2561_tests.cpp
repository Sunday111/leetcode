#include "2561.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, std::vector<int>>,
    long>(R"cases(
[4,2,2,2] [1,4,1,2] 1
)cases");

using t2561 = SolutionTests<Solution>;

TEST_P(t2561, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minCost(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2561,
    t2561::parameters(kCases.size()),
    t2561::name);
