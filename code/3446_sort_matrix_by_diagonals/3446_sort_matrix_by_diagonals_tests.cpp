#include <print>

#include "3446_sort_matrix_by_diagonals.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::sortMatrix;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,7,3],[9,8,2],[4,5,6]] [[8,2,3],[9,6,7],[4,5,1]]
)cases");

class t3446_sort_matrix_by_diagonals : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3446_sort_matrix_by_diagonals, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.sortMatrix(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3446_sort_matrix_by_diagonals,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
