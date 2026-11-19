#include "0279_perfect_squares.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numSquares;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
12 3

13 2

1 1

7168 4

7217 3
)cases");

class t0279_perfect_squares : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0279_perfect_squares, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.numSquares(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0279_perfect_squares,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
