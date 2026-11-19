#include "2094_finding_3_digit_even_numbers.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findEvenNumbers;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3] [132,312]

[2,1,3,0] [102,120,130,132,210,230,302,310,312,320]

[2,2,8,8,2] [222,228,282,288,822,828,882]

[3,7,5] []
)cases");

class t2094_finding_3_digit_even_numbers
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2094_finding_3_digit_even_numbers, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.findEvenNumbers(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2094_finding_3_digit_even_numbers,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
