#include "3275_kth_nearest_obstacle.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::resultsArray;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2],[3,4],[2,3],[-3,0]] 2 [-1,7,5,3]
)cases");

class t3275_kth_nearest_obstacle : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3275_kth_nearest_obstacle, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.resultsArray(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3275_kth_nearest_obstacle,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
