#include "1668_maximum_repeating_substring.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxRepeating;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"ababc" "ab" 2

"ababc" "ba" 1

"ababc" "ac" 0

"aaabaaaabaaabaaaabaaaabaaaabaaaaba" "aaaba" 5
)cases");

class t1668_maximum_repeating_substring
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1668_maximum_repeating_substring, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxRepeating(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1668_maximum_repeating_substring,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
