#include "3775_reverse_words_with_same_vowel_count.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::reverseWords;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"cat and mice" "cat dna mice"
)cases");

class t3775_reverse_words_with_same_vowel_count
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3775_reverse_words_with_same_vowel_count, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.reverseWords(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3775_reverse_words_with_same_vowel_count,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
