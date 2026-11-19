#include "3715_sum_of_perfect_ancestors.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::sumOfAncestors;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 [[0,1],[1,2]] [2,8,2] 3

3 [[0,1],[0,2]] [1,2,4] 1

4 [[0,1],[0,2],[1,3]] [1,2,9,4] 2
)cases");

class t3715_sum_of_perfect_ancestors : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3715_sum_of_perfect_ancestors, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.sumOfAncestors(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3715_sum_of_perfect_ancestors,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
