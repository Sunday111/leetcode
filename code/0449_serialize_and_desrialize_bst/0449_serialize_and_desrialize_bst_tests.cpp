#include "0449_serialize_and_desrialize_bst.hpp"
#include "gtest/gtest.h"

bool TestCase(std::string_view s)
{
    return Codec::serialize(Codec::deserialize(s)) == s;
}

TEST(t0449_serialize_and_desrialize_bst, test_1)
{
    TestCase("2b,1n,3n");
}

TEST(t0449_serialize_and_desrialize_bst, test_2)
{
    TestCase("");
}
