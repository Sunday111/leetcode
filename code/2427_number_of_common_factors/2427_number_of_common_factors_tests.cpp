#include "2427_number_of_common_factors.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::commonFactors;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
12 6 4

25 30 2
)cases");

using t2427_number_of_common_factors = SolutionTests<Solution>;

TEST_P(t2427_number_of_common_factors, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.commonFactors(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2427_number_of_common_factors,
    t2427_number_of_common_factors::parameters(kCases.size()),
    t2427_number_of_common_factors::name);
