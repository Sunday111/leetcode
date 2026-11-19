#include "1079_letter_tile_possibilities.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numTilePossibilities;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"AAB" 8

"AAABBC" 188

"V" 1
)cases");

class t1079_letter_tile_possibilities : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1079_letter_tile_possibilities, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.numTilePossibilities(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1079_letter_tile_possibilities,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
