#include <string>
#include <string_view>

#include "3714_longest_balanced_substring_ii.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestBalanced;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abbac" 4

"aabcc" 3

"aba" 2

"bacbbc" 4
)cases");

class t3714_longest_balanced_substring_ii
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3714_longest_balanced_substring_ii, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.longestBalanced(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3714_longest_balanced_substring_ii,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
