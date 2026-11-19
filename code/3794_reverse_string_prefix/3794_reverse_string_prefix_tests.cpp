#include "3794_reverse_string_prefix.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::reversePrefix;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcd" 2 "bacd"
)cases");

class t3794_reverse_string_prefix : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3794_reverse_string_prefix, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.reversePrefix(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3794_reverse_string_prefix,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
