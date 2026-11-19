#include "3847_find_the_score_difference_in_a_game.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::scoreDifference;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3] 0

[2,4,2,1,2,1] 4

[1] -1
)cases");

class t3847_find_the_score_difference_in_a_game
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3847_find_the_score_difference_in_a_game, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.scoreDifference(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3847_find_the_score_difference_in_a_game,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
