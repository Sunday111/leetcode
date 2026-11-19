#include "2322_minimum_score_after_removals_on_a_tree.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumScore;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[5,5,2,4,4,2] [[0,1],[1,2],[5,2],[4,3],[1,3]] 0

[1,5,5,4,11] [[0,1],[1,2],[1,3],[3,4]] 9
)cases");

class t2322_minimum_score_after_removals_on_a_tree
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2322_minimum_score_after_removals_on_a_tree, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minimumScore(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2322_minimum_score_after_removals_on_a_tree,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
