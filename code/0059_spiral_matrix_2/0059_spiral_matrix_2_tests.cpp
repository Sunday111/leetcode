#include "0059_spiral_matrix_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::generateMatrix;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 [[1,2,3],[8,9,4],[7,6,5]]
)cases");

class t0059_spiral_matrix_2 : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0059_spiral_matrix_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.generateMatrix(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0059_spiral_matrix_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
