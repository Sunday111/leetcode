#include "0001_two_sum.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, int>,
    std::vector<int>>(R"(
[2,7,11,15] 9 [0,1]
[3,2,4] 6 [1,2]
[3,3] 6 [0,1]
)");

class t0001_two_sum : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0001_two_sum, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [nums, target] = inputs;
    auto actual = Solution{}.twoSum(nums, target);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0001_two_sum,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
