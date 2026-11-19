#include "2943_maximize_area_of_square_hole_in_grid.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maximizeSquareHoleArea;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
2 1 [2,3] [2] 4

1 1 [2] [2] 4

3 2 [3,2,4] [3,2] 9

4 40 [5,3,2,4] [36,41,6,34,33] 9
)cases");

class t2943_maximize_area_of_square_hole_in_grid
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2943_maximize_area_of_square_hole_in_grid, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args)
        { return Solution{}.maximizeSquareHoleArea(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2943_maximize_area_of_square_hole_in_grid,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
