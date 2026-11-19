#include "0064_minimum_path_sum_2.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minPathSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,3,1],[1,5,1],[4,2,1]] 7

[[1,2,3],[4,5,6]] 12
)cases");

class t0064_minimum_path_sum_2 : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0064_minimum_path_sum_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minPathSum(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0064_minimum_path_sum_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
