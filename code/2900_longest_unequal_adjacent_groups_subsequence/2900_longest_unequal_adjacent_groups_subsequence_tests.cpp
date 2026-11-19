#include "2900_longest_unequal_adjacent_groups_subsequence.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::getLongestSubsequence;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["d","g"] [0,1] ["d","g"]
)cases");

class t2900_longest_unequal_adjacent_groups_subsequence
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2900_longest_unequal_adjacent_groups_subsequence, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.getLongestSubsequence(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2900_longest_unequal_adjacent_groups_subsequence,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
