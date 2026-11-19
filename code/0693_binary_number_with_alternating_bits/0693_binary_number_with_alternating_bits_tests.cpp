#include "0693_binary_number_with_alternating_bits.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::hasAlternatingBits;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
5 true

7 false

11 false
)cases");

class t0693_binary_number_with_alternating_bits
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0693_binary_number_with_alternating_bits, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.hasAlternatingBits(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0693_binary_number_with_alternating_bits,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
