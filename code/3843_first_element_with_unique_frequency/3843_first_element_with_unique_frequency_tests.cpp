#include "3843_first_element_with_unique_frequency.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, int>(R"cases(
[20,10,30,30] 30

[20,20,10,30,30,30] 20

[10,10,20,20] -1
)cases");

using t3843_first_element_with_unique_frequency = SolutionTests<Solution>;

TEST_P(t3843_first_element_with_unique_frequency, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.firstUniqueFreq(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3843_first_element_with_unique_frequency,
    t3843_first_element_with_unique_frequency::parameters(kCases.size()),
    t3843_first_element_with_unique_frequency::name);
