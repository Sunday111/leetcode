#include "0799_champagne_tower.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::champagneTower;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 1 1 0

2 1 1 0.5

100000009 33 17 1
)cases");

class t0799_champagne_tower : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0799_champagne_tower, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.champagneTower(args...); },
        inputs);
    ASSERT_NEAR(expected, actual, 0.001);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0799_champagne_tower,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
