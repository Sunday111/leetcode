#include "2099_find_subsequence_of_length_k_with_largest_sum.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxSubsequence;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[50,-75] 2 [50,-75]
)cases");

class t2099_find_subsequence_of_length_k_with_largest_sum
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2099_find_subsequence_of_length_k_with_largest_sum, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxSubsequence(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2099_find_subsequence_of_length_k_with_largest_sum,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
