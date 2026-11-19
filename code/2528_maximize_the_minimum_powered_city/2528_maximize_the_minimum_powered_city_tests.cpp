#include "2528_maximize_the_minimum_powered_city.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxPower;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[4,4,4,4] 0 3 4
)cases");

class t2528_maximize_the_minimum_powered_city
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2528_maximize_the_minimum_powered_city, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxPower(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2528_maximize_the_minimum_powered_city,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
