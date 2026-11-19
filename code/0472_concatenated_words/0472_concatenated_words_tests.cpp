#include "0472_concatenated_words.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest =
    &Solution::findAllConcatenatedWordsInADict;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
["catsdogcats","dogcatsdog","ratcatdogcat"]
)cases");

class t0472_concatenated_words : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0472_concatenated_words, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args)
        { return Solution{}.findAllConcatenatedWordsInADict(args...); },
        inputs);
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0472_concatenated_words,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
