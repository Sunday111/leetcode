#include "1292_maximum_side_length_of_a_square_with_sum_less_than_or_equal_to_threshold.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxSideLength;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]] 4 2
)cases");

class
    t1292_maximum_side_length_of_a_square_with_sum_less_than_or_equal_to_threshold
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(
    t1292_maximum_side_length_of_a_square_with_sum_less_than_or_equal_to_threshold,
    Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maxSideLength(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1292_maximum_side_length_of_a_square_with_sum_less_than_or_equal_to_threshold,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
