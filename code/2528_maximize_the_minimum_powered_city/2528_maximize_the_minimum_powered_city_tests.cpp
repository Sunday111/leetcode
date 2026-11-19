#include "2528_maximize_the_minimum_powered_city.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxPower;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[4,4,4,4] 0 3 4
)cases");

using t2528_maximize_the_minimum_powered_city = SolutionTests<Solution>;

TEST_P(t2528_maximize_the_minimum_powered_city, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxPower(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2528_maximize_the_minimum_powered_city,
    t2528_maximize_the_minimum_powered_city::parameters(kCases.size()),
    t2528_maximize_the_minimum_powered_city::name);
