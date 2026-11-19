#include "2901_longest_unequal_adjacent_groups_subsequence_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::getWordsInLongestSubsequence;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["a","b","c","d"] [1,2,3,4] ["a","b","c","d"]

["bdb","aaa","ada"] [2,1,3] ["aaa","ada"]
)cases");

class t2901_longest_unequal_adjacent_groups_subsequence_2
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2901_longest_unequal_adjacent_groups_subsequence_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args)
        { return Solution{}.getWordsInLongestSubsequence(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2901_longest_unequal_adjacent_groups_subsequence_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
