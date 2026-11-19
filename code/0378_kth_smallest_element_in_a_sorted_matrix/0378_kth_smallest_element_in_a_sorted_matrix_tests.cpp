#include <algorithm>

#include "0378_kth_smallest_element_in_a_sorted_matrix.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<int>>, int>,
    int>(R"cases(
[[1,5,9],[10,11,13],[12,13,15]] 1 1
[[1,5,9],[10,11,13],[12,13,15]] 8 13
[[-5]] 1 -5
)cases");

class t0378_kth_smallest_element_in_a_sorted_matrix
    : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0378_kth_smallest_element_in_a_sorted_matrix, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [matrix, k] = inputs;
    ASSERT_EQ(expected, Solution{}.kthSmallest(matrix, k));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0378_kth_smallest_element_in_a_sorted_matrix,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
