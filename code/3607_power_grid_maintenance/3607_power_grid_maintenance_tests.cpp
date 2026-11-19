#include "3607_power_grid_maintenance.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<
        unsigned int,
        std::vector<std::vector<int>>,
        std::vector<std::vector<int>>>,
    std::vector<int>>(R"cases(
5 [[1,2],[2,3],[3,4],[4,5]] [[1,3],[2,1],[1,1],[2,2],[1,2]] [3,2,3]
)cases");

class t3607_power_grid_maintenance : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3607_power_grid_maintenance, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.processQueries(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3607_power_grid_maintenance,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
