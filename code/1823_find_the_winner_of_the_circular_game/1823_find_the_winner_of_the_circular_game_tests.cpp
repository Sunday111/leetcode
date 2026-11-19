#include "1823_find_the_winner_of_the_circular_game.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<uint16_t, uint16_t>, uint16_t>(
        R"cases(
5 2 3
6 5 1
1 1 1
)cases");

class t1823_find_the_winner_of_the_circular_game
    : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t1823_find_the_winner_of_the_circular_game, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto [n, k] = inputs;
    ASSERT_EQ(expected, Solution::findTheWinner(n, k));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1823_find_the_winner_of_the_circular_game,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
