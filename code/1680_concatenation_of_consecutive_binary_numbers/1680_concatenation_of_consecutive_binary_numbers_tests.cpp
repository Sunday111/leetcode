#include "1680_concatenation_of_consecutive_binary_numbers.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::concatenatedBinary;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 1

3 27

12 505379714

90999 459883164

100000 757631812
)cases");

class t1680_concatenation_of_consecutive_binary_numbers
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1680_concatenation_of_consecutive_binary_numbers, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.concatenatedBinary(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1680_concatenation_of_consecutive_binary_numbers,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
