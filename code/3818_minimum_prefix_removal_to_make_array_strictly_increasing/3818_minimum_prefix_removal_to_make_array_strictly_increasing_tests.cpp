#include "3818_minimum_prefix_removal_to_make_array_strictly_increasing.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumPrefixLength;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,-1,2,3,3,4,5] 4

[4,3,-2,-5] 3

[1,2,3,4] 0
)cases");

class t3818_minimum_prefix_removal_to_make_array_strictly_increasing
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3818_minimum_prefix_removal_to_make_array_strictly_increasing, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minimumPrefixLength(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3818_minimum_prefix_removal_to_make_array_strictly_increasing,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
