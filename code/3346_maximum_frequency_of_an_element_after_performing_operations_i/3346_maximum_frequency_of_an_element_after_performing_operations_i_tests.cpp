#include "3346_maximum_frequency_of_an_element_after_performing_operations_i.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxFrequency;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[5,11,20,20] 5 1 2

[88,53] 27 2 2
)cases");

using t3346_maximum_frequency_of_an_element_after_performing_operations_i =
    SolutionTests<Solution>;

TEST_P(
    t3346_maximum_frequency_of_an_element_after_performing_operations_i,
    Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxFrequency(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3346_maximum_frequency_of_an_element_after_performing_operations_i,
    t3346_maximum_frequency_of_an_element_after_performing_operations_i::
        parameters(kCases.size()),
    t3346_maximum_frequency_of_an_element_after_performing_operations_i::name);
