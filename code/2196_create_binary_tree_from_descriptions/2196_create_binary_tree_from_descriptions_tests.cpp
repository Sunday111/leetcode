#include "2196_create_binary_tree_from_descriptionstest_cases.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

class t2196_create_binary_tree_from_descriptions
    : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2196_create_binary_tree_from_descriptions, MinOperations)
{
    auto [inputs, expected] = kCases[GetParam()];
    auto node = Solution{}.createBinaryTree(std::get<0>(inputs));
    ASSERT_TRUE(CompareBinaryTrees(expected.root, node));
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2196_create_binary_tree_from_descriptions,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
