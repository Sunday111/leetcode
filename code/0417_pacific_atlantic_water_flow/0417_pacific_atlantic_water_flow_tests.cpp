#include <print>

#include "0417_pacific_atlantic_water_flow.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

static constexpr auto kMethodToTest = &Solution::pacificAtlantic;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
[[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
)cases");

class t0417_pacific_atlantic_water_flow
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0417_pacific_atlantic_water_flow, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.pacificAtlantic(args...); },
        inputs);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0417_pacific_atlantic_water_flow,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
