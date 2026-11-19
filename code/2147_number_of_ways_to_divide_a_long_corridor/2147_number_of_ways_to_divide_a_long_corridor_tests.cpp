#include "2147_number_of_ways_to_divide_a_long_corridor.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numberOfWays;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"SSPPSPS" 3

"PPSPSP" 1

"S" 0

"P" 0
)cases");

class t2147_number_of_ways_to_divide_a_long_corridor
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2147_number_of_ways_to_divide_a_long_corridor, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.numberOfWays(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2147_number_of_ways_to_divide_a_long_corridor,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
