#include "3459_length_of_longest_v_shaped_diagonal_segment.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::lenOfVDiagonal;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[2,2,1,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]] 5

[[2,2,2,2,2],[2,0,2,2,0],[2,0,1,1,0],[1,0,2,2,2],[2,0,0,2,2]] 4

[[1,2,2,2,2],[2,2,2,2,0],[2,0,0,0,0],[0,0,2,2,2],[2,0,0,2,0]] 5

[[1]] 1

[[2,0],[0,1]] 2

[[1,2,0,0],[0,0,1,2]] 2
)cases");

class t3459_length_of_longest_v_shaped_diagonal_segment
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3459_length_of_longest_v_shaped_diagonal_segment, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.lenOfVDiagonal(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3459_length_of_longest_v_shaped_diagonal_segment,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
