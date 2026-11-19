#include "2225_find_players_with_zero_or_one_losses.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findWinners;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,3],[2,3],[3,6],[5,6],[5,7],[4,5],[4,8],[4,9],[10,4],[10,9]] [[1,2,10],[4,5,7,8]]

[[2,3],[1,3],[5,4],[6,4]] [[1,2,5,6],[]]
)cases");

class t2225_find_players_with_zero_or_one_losses
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2225_find_players_with_zero_or_one_losses, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.findWinners(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2225_find_players_with_zero_or_one_losses,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
