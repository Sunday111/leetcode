#include "1498_number_of_subsequences_that_satisfy_the_given_sum_condition.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>, u32>, u32>(R"cases(
[3,5,6,7] 9 4
[5,2,4,1,7,6,8] 16 127
)cases");

class t1498_number_of_subsequences_that_satisfy_the_given_sum_condition
    : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t1498_number_of_subsequences_that_satisfy_the_given_sum_condition, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [nums, target] = inputs;
    ASSERT_EQ(expected, Solution{}.numSubseq(nums, target));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1498_number_of_subsequences_that_satisfy_the_given_sum_condition,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
