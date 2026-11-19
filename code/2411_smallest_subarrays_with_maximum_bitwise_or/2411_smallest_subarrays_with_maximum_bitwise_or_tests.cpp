#include "2411_smallest_subarrays_with_maximum_bitwise_or.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::smallestSubarrays;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0] [1]

[1,0,2,1,3] [3,3,2,2,1]
)cases");

class t2411_smallest_subarrays_with_maximum_bitwise_or
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2411_smallest_subarrays_with_maximum_bitwise_or, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.smallestSubarrays(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2411_smallest_subarrays_with_maximum_bitwise_or,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
