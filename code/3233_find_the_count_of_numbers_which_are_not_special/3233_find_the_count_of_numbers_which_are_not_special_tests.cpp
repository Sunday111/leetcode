#include "3233_find_the_count_of_numbers_which_are_not_special.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::nonSpecialCount;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
5 7 3

4 16 11

1 100000 99935

1 4 3
)cases");

class t3233_find_the_count_of_numbers_which_are_not_special
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3233_find_the_count_of_numbers_which_are_not_special, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.nonSpecialCount(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3233_find_the_count_of_numbers_which_are_not_special,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
