#include <print>

#include "0289_game_of_life.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<int>>>,
    std::vector<std::vector<int>>>(R"cases(
[[0,1,0],[0,0,1],[1,1,1],[0,0,0]] [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
)cases");

class t0289_game_of_life : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0289_game_of_life, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    std::apply(
        [](auto&... args) { return Solution{}.gameOfLife(args...); },
        inputs);
    auto& actual = std::get<0>(inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0289_game_of_life,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
