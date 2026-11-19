#include "2311_longest_binary_subsequence_less_than_or_equal_to_k.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestSubsequence;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"1001010" 5 5
)cases");

class t2311_longest_binary_subsequence_less_than_or_equal_to_k
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2311_longest_binary_subsequence_less_than_or_equal_to_k, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.longestSubsequence(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2311_longest_binary_subsequence_less_than_or_equal_to_k,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
