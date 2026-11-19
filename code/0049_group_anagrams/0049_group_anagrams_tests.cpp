#include "0049_group_anagrams.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

static constexpr auto kMethodToTest = &Solution::groupAnagrams;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["eat","tea","tan","ate","nat","bat"] [["ate","eat","tea"],["bat"],["nat","tan"]]
)cases");

class t0049_group_anagrams : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0049_group_anagrams, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.groupAnagrams(args...); },
        inputs);
    ASSERT_EQ(sorted(expected), sorted(actual));
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0049_group_anagrams,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
