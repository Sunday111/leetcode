#include "0273_integer_to_english_words.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numberToWords;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
123 "One Hundred Twenty Three"

12345 "Twelve Thousand Three Hundred Forty Five"

1234567 "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

1234567891
"One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"
)cases");

class t0273_integer_to_english_words : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0273_integer_to_english_words, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.numberToWords(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0273_integer_to_english_words,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
