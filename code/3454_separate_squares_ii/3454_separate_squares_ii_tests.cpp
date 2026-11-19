#include "3454_separate_squares_ii.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::separateSquares;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[0,0,1],[2,2,1]] 1

[[0,0,2],[1,1,1]] 1

[[15,21,2],[19,21,3]] 22.3
)cases");

class t3454_separate_squares_ii : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3454_separate_squares_ii, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.separateSquares(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3454_separate_squares_ii,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
