#include "0696_count_binary_substrings.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countBinarySubstrings;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"00110011" 6
)cases");

class t0696_count_binary_substrings : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0696_count_binary_substrings, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.countBinarySubstrings(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0696_count_binary_substrings,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
