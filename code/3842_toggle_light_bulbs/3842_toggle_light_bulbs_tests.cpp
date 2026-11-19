#include "3842_toggle_light_bulbs.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::toggleLightBulbs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[10,30,20,10] [20,30]

[100,100] []
)cases");

class t3842_toggle_light_bulbs : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3842_toggle_light_bulbs, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.toggleLightBulbs(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3842_toggle_light_bulbs,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
