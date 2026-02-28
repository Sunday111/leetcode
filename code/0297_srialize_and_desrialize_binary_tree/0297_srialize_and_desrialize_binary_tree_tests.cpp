#include "0297_srialize_and_desrialize_binary_tree.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

bool TestCase(std::string_view s)
{
    auto node = Codec::deserialize(s);
    bool result = Codec::serialize(node) == s;
    DeleteBinaryTree(node);
    return result;
}

TEST(t0297_srialize_and_desrialize_binary_tree, test_1)
{
    TestCase("1b,2n,3b,4n,5n");
}

TEST(t0297_srialize_and_desrialize_binary_tree, test_2)
{
    TestCase("");
}

TEST(t0297_srialize_and_desrialize_binary_tree, test_3)
{
    TestCase("1b,2n,-13b,4n,5n");
}

TEST(t0297_srialize_and_desrialize_binary_tree, test_4)
{
    TestCase("1l,2n");
}

TEST(t0297_srialize_and_desrialize_binary_tree, test_5)
{
    TestCase("1n");
}
