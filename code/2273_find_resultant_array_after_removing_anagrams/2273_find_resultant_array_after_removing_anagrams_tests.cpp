#include "2273_find_resultant_array_after_removing_anagrams.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::removeAnagrams;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["a","b","c","d","e"] ["a","b","c","d","e"]

["abba","baba","bbaa","cd","cd"] ["abba","cd"]
)cases");

class t2273_find_resultant_array_after_removing_anagrams
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2273_find_resultant_array_after_removing_anagrams, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.removeAnagrams(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2273_find_resultant_array_after_removing_anagrams,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
