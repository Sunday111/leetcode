#include "1931_painting_a_grid_with_tree_different_colors.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<int, int>, int>(R"cases(
3 1 12

3 2 54

3 3 246
)cases");

class t1931_painting_a_grid_with_tree_different_colors
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1931_painting_a_grid_with_tree_different_colors, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.colorTheGrid(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1931_painting_a_grid_with_tree_different_colors,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
