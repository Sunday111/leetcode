#include "2196_test_cases.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

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
