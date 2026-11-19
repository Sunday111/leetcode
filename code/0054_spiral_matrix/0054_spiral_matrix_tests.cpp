#include "0054_spiral_matrix.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::spiralOrder;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2,3],[4,5,6],[7,8,9]] [1,2,3,6,9,8,7,4,5]
)cases");

class t0054_spiral_matrix : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0054_spiral_matrix, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.spiralOrder(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0054_spiral_matrix,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
