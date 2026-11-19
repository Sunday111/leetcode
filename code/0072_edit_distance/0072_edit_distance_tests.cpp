#include "0072_edit_distance.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minDistance;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"horse" "ros" 3

"intention" "execution" 5

"" "" 0

"abc" "defghi" 6

"leet" "code" 4

"azertyqsdfghqwerty" "azertyjklmqwerty" 6

"aaaaaaaaaaaaaaaaaaaaaa" "aaaaaaaaaaaaaav" 8

"aaayuio" "hjklaaa" 7

"sea" "eat" 2
)cases");

class t0072_edit_distance : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0072_edit_distance, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minDistance(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0072_edit_distance,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
