#include "0045_jump_game_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, unsigned int>(
        R"cases(
[2,3,1,1,4] 2

[2,3,0,1,4] 2

[0] 0
)cases");

class t0045_jump_game_2 : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0045_jump_game_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.jump(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0045_jump_game_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
