#include "0966_vowel_spellcheck.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::spellchecker;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["KiTe","kite","hare","Hare"]
["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
)cases");

class t0966_vowel_spellcheck : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0966_vowel_spellcheck, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.spellchecker(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0966_vowel_spellcheck,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
