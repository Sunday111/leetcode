#include "0868_binary_gap.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::binaryGap;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
22 2

8 0

5 2
)cases");

class t0868_binary_gap : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0868_binary_gap, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.binaryGap(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0868_binary_gap,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
