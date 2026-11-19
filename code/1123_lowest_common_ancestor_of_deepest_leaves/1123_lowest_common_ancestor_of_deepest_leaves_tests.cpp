#include "1123_lowest_common_ancestor_of_deepest_leaves.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::lcaDeepestLeaves;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[3,5,1,6,2,0,8,null,null,7,4] [2,7,4]
)cases");

class t1123_lowest_common_ancestor_of_deepest_leaves
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1123_lowest_common_ancestor_of_deepest_leaves, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.lcaDeepestLeaves(args...); },
        inputs);
    ASSERT_TRUE(CompareBinaryTrees(expected.root, actual));
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1123_lowest_common_ancestor_of_deepest_leaves,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
