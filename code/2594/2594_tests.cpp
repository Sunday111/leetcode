#include "2594.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::repairCars;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3,4] 10 16
)cases");

using t2594 = SolutionTests<Solution>;

TEST_P(t2594, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.repairCars(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2594,
    t2594::parameters(kCases.size()),
    t2594::name);
