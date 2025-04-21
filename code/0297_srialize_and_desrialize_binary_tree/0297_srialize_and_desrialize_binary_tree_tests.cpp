#include "0297_srialize_and_desrialize_binary_tree.hpp"
#include "gtest/gtest.h"

bool TestCase(std::string_view s)
{
    return Codec::serialize(Codec::deserialize(s)) == s;
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
