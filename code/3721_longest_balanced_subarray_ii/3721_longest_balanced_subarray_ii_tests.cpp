#include "3721_longest_balanced_subarray_ii.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, u32>(R"cases(
[2,5,4,3] 4
[3,2,2,5,4] 5
[1,2,3,2] 3
[19,5,41,39,39,23,20] 2
)cases");

class t3721_longest_balanced_subarray_ii
    : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t3721_longest_balanced_subarray_ii, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    ASSERT_EQ(expected, Solution{}.longestBalanced(std::get<0>(inputs)));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3721_longest_balanced_subarray_ii,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
