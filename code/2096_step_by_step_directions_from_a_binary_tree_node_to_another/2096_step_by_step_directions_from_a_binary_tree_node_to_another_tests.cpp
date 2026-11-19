#include "2096_step_by_step_directions_from_a_binary_tree_node_to_another.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::getDirections;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[5,1,2,3,null,6,4] 3 6 "UURL"
)cases");

class t2096_step_by_step_directions_from_a_binary_tree_node_to_another
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2096_step_by_step_directions_from_a_binary_tree_node_to_another, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.getDirections(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2096_step_by_step_directions_from_a_binary_tree_node_to_another,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
