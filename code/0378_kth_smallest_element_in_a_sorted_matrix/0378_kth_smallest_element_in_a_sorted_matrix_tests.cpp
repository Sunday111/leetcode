#include <algorithm>

#include "0378_kth_smallest_element_in_a_sorted_matrix.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<int>>, int>,
    int>(R"cases(
[[1,5,9],[10,11,13],[12,13,15]] 1 1
[[1,5,9],[10,11,13],[12,13,15]] 8 13
[[-5]] 1 -5
)cases");

using t0378_kth_smallest_element_in_a_sorted_matrix = SolutionTests<Solution>;
TEST_P(t0378_kth_smallest_element_in_a_sorted_matrix, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto& [matrix, k] = inputs;
            ASSERT_EQ(expected, solution.kthSmallest(matrix, k));
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0378_kth_smallest_element_in_a_sorted_matrix,
    t0378_kth_smallest_element_in_a_sorted_matrix::parameters(kCases.size()),
    t0378_kth_smallest_element_in_a_sorted_matrix::name);
