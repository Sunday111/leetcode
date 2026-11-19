#include "3314_construct_the_minimum_bitwise_array_i.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minBitwiseArray;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[2,3,5,7] [-1,1,4,3]

[11,13,31] [9,12,15]
)cases");

class t3314_construct_the_minimum_bitwise_array_i
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3314_construct_the_minimum_bitwise_array_i, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minBitwiseArray(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3314_construct_the_minimum_bitwise_array_i,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
