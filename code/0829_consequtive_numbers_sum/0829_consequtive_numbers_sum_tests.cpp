#include "0829_consequtive_numbers_sum.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::consecutiveNumbersSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
5 2

9 3

15 4

999999 64

99999999 48
)cases");

class t0829_consequtive_numbers_sum : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0829_consequtive_numbers_sum, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.consecutiveNumbersSum(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0829_consequtive_numbers_sum,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
