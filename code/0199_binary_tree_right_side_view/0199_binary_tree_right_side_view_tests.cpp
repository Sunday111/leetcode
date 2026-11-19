#include "0199_binary_tree_right_side_view.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::rightSideView;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3,4,null,null,null,5] [1,3,4,5]
)cases");

class t0199_binary_tree_right_side_view
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0199_binary_tree_right_side_view, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.rightSideView(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0199_binary_tree_right_side_view,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
