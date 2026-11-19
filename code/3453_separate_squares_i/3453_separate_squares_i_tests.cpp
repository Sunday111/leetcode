#include "3453_separate_squares_i.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::separateSquares;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[0,0,2],[1,1,1]] 1.1666641235351562
)cases");

class t3453_separate_squares_i : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3453_separate_squares_i, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.separateSquares(args...); },
        inputs);
    ASSERT_NEAR(expected, actual, 0.00001);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3453_separate_squares_i,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
