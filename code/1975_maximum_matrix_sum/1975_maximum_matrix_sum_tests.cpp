#include "1975_maximum_matrix_sum.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxMatrixSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,-1],[-1,1]] 4

[[1,2,3],[-1,-2,-3],[1,2,3]] 16

[[2,9,3],[5,4,-4],[1,7,1]] 34

[[-10000,-10000,-10000],[-10000,-10000,-10000],[-10000,-10000,-10000]] 70000
)cases");

class t1975_maximum_matrix_sum : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1975_maximum_matrix_sum, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxMatrixSum(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1975_maximum_matrix_sum,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
