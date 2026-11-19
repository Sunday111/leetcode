#include "2163_minimum_difference_in_sums_after_removal_of_elements.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, int64_t>(R"cases(
[3,1,2] -1
)cases");

using t2163_minimum_difference_in_sums_after_removal_of_elements =
    SolutionTests<all_branches::Solution>;
TEST_P(t2163_minimum_difference_in_sums_after_removal_of_elements, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            ASSERT_EQ(
                expected,
                solution.minimumDifference(std::get<0>(inputs)));
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2163_minimum_difference_in_sums_after_removal_of_elements,
    t2163_minimum_difference_in_sums_after_removal_of_elements::parameters(
        kCases.size()),
    t2163_minimum_difference_in_sums_after_removal_of_elements::name);
