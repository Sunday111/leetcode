#include "1411_num_of_ways.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numOfWays;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 12

5000 30228214
)cases");

class t1411_num_of_ways : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1411_num_of_ways, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.numOfWays(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1411_num_of_ways,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
