#include "0885_spiral_matrix_3.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::spiralMatrixIII;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 4 0 0 [[0,0],[0,1],[0,2],[0,3]]
)cases");

class t0885_spiral_matrix_3 : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0885_spiral_matrix_3, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.spiralMatrixIII(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0885_spiral_matrix_3,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
