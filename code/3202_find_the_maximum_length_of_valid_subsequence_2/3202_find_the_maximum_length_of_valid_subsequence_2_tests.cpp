#include "3202_find_the_maximum_length_of_valid_subsequence_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maximumLength;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3,4,5] 2 5

[1,9,3,10,10] 4 2
)cases");

class t3202_find_the_maximum_length_of_valid_subsequence_2
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3202_find_the_maximum_length_of_valid_subsequence_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maximumLength(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3202_find_the_maximum_length_of_valid_subsequence_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
