#include "0712_minimum_ascii_delete_sum_for_two_strings.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumDeleteSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"sea" "eat" 231

"delete" "leet" 403
)cases");

class t0712_minimum_ascii_delete_sum_for_two_strings
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0712_minimum_ascii_delete_sum_for_two_strings, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minimumDeleteSum(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0712_minimum_ascii_delete_sum_for_two_strings,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
