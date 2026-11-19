#include <algorithm>

#include "0140_word_break_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::string_view, std::vector<std::string>>,
    std::vector<std::string>>(R"cases(
"catsanddog" ["and","cat","cats","dog","sand"] ["cat sand dog","cats and dog"]

"pineapplepenapple"
["apple","applepen","pen","pine","pineapple"]
["pine apple pen apple","pine applepen apple","pineapple pen apple"]
)cases");

class t0140_word_break_2 : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0140_word_break_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.wordBreak(args...); },
        inputs);
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0140_word_break_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
