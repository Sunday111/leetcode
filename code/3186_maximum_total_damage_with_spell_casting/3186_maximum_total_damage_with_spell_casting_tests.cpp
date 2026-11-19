#include "3186_maximum_total_damage_with_spell_casting.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maximumTotalDamage;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[7,1,6,6] 13

[3,4,5,6,6,7,1,1,1,1,1,9,9,9,9,9,9,9,9,9,6] 104
)cases");

class t3186_maximum_total_damage_with_spell_casting
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3186_maximum_total_damage_with_spell_casting, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maximumTotalDamage(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3186_maximum_total_damage_with_spell_casting,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
