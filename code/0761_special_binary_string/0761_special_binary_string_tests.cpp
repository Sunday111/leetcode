#include "0761_special_binary_string.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::makeLargestSpecial;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"11011000" "11100100"

"10" "10"

"110110100100" "111010010100"

"11001011101000101100" "11101000110011001010"
)cases");

class t0761_special_binary_string : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0761_special_binary_string, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.makeLargestSpecial(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0761_special_binary_string,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
