#include "0053_maximum_subarray.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, int>(R"cases(
[-2,1,-3,4,-1,2,1,-5,4] 6

[1] 1

[5,4,-1,7,8] 23
)cases");

class t0053_maximum_subarray : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0053_maximum_subarray, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxSubArray(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0053_maximum_subarray,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
