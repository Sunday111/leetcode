#include "0017_letter_combinations_of_a_phone_number.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

static constexpr auto kMethodToTest = &Solution::letterCombinations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"23" ["ad","ae","af","bd","be","bf","cd","ce","cf"]
)");

class t0017_letter_combinations_of_a_phone_number
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0017_letter_combinations_of_a_phone_number, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.letterCombinations(args...); },
        inputs);
    ASSERT_EQ(sorted(expected), sorted(actual));
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0017_letter_combinations_of_a_phone_number,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
