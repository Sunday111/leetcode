#include "2509_cycle_length_queries_in_a_tree.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::cycleLengthQueries;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
2 [[1,2]] [2]

3 [[5,3],[4,7],[2,3]] [4,5,3]

5 [[17,21],[23,5],[15,7],[3,21],[31,9],[5,15],[11,2],[19,7]] [7,3,2,6,8,6,3,7]
)cases");

class t2509_cycle_length_queries_in_a_tree
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2509_cycle_length_queries_in_a_tree, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.cycleLengthQueries(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2509_cycle_length_queries_in_a_tree,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
