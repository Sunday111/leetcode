#include "0837_new_game.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::new21Game;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
10 1 10 1.0000000149011612

1 0 1 1
)cases");

class t0837_new_game : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0837_new_game, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.new21Game(args...); },
        inputs);
    ASSERT_FLOAT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0837_new_game,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
