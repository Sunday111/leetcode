#include "2163_minimum_difference_in_sums_after_removal_of_elements.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, int64_t>(R"cases(
[3,1,2] -1
)cases");

class t2163_minimum_difference_in_sums_after_removal_of_elements
    : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t2163_minimum_difference_in_sums_after_removal_of_elements, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    ASSERT_EQ(
        expected,
        all_branches::Solution{}.minimumDifference(std::get<0>(inputs)));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2163_minimum_difference_in_sums_after_removal_of_elements,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
