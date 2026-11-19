#include "2566_maximum_difference_by_remapping_a_digit.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minMaxDifference;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1001 9009
)cases");

class t2566_maximum_difference_by_remapping_a_digit
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2566_maximum_difference_by_remapping_a_digit, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minMaxDifference(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2566_maximum_difference_by_remapping_a_digit,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
