#include <print>

#include "0407_trapping_rain_water.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::trapRainWater;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]] 4
)cases");

class t0407_trapping_rain_water : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0407_trapping_rain_water, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.trapRainWater(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0407_trapping_rain_water,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
