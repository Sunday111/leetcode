#include "0449_serialize_and_desrialize_bst.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

bool TestCase(std::string_view s)
{
    auto x = Codec::deserialize(s);
    bool result = Codec::serialize(x) == s;
    DeleteBinaryTree(x);
    return result;
}

TEST(t0449_serialize_and_desrialize_bst, test_1)
{
    TestCase("2b,1n,3n");
}

TEST(t0449_serialize_and_desrialize_bst, test_2)
{
    TestCase("");
}
