#include "2594_minimum_time_to_repair_cars.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::repairCars;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3,4] 10 16
)cases");

using t2594_minimum_time_to_repair_cars = SolutionTests<Solution>;

TEST_P(t2594_minimum_time_to_repair_cars, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.repairCars(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2594_minimum_time_to_repair_cars,
    t2594_minimum_time_to_repair_cars::parameters(kCases.size()),
    t2594_minimum_time_to_repair_cars::name);
