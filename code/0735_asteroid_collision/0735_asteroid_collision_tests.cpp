#include "0735_asteroid_collision.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::asteroidCollision;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[10,2,-5] [10]

[-2,-1,1,2] [-2,-1,1,2]
)cases");

class t0735_asteroid_collision : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0735_asteroid_collision, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.asteroidCollision(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0735_asteroid_collision,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
