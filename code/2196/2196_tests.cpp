#include "2196.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::createBinaryTree;
/*inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]] "[50,20,80,15,17,19]"
[[1,2,1],[2,3,0],[3,4,1]] "[1,2,null,null,3,4]"
)");*/

inline static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<int>>>,
    LeetCodeBinaryTree<TreeNode>>(R"(
[[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]] [50,20,80,15,17,19]
[[1,2,1],[2,3,0],[3,4,1]] [1,2,null,null,3,4]
)");

class t2196 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2196, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);

    EXPECT_TRUE(CompareBinaryTrees(expected.root, actual));
    // DeleteBinaryTree(actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2196,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
