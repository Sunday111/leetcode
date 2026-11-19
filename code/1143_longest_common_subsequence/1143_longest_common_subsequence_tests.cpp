#include "1143_longest_common_subsequence.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestCommonSubsequence;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcde" "ace" 3

"abc" "abc" 3

"abc" "def" 0

"a" "ttta" 1

"wggi" "g" 1

"iitt" "tttttttttt" 2

"jijiijjpji" "jjji" 4
)cases");

class t1143_longest_common_subsequence : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1143_longest_common_subsequence, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args)
        { return Solution{}.longestCommonSubsequence(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1143_longest_common_subsequence,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
