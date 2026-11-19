#include "3625_count_number_of_trapezoids_2_alt_5.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countTrapezoids;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[0,0],[1,0],[0,1],[2,1]] 1

[[-3,2],[3,0],[2,3],[3,2],[2,-3]] 2

[[71,-89],[-75,-89],[-9,11],[-24,-89],[-51,-89],[-77,-89],[42,11]] 10
)cases");

class t3625_count_number_of_trapezoids_2
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3625_count_number_of_trapezoids_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.countTrapezoids(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3625_count_number_of_trapezoids_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
