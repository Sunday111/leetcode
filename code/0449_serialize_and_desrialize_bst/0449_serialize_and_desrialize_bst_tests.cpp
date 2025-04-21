#include "0449_serialize_and_desrialize_bst.hpp"
#include "gtest/gtest.h"

TEST(t0449_serialize_and_desrialize_bst, test_1)
{
    std::println("{}", Codec::serialize(Codec::deserialize("1b,2n,3b,4n,5n")));
}

TEST(t0449_serialize_and_desrialize_bst, test_2)
{
    std::println("{}", Codec::serialize(Codec::deserialize("")));
}

TEST(t0449_serialize_and_desrialize_bst, test_3)
{
    std::println(
        "{}",
        Codec::serialize(Codec::deserialize("1b,2n,-13b,4n,5n")));
}

TEST(t0449_serialize_and_desrialize_bst, test_4)
{
    std::println("{}", Codec::serialize(Codec::deserialize("1l,2n")));
}

TEST(t0449_serialize_and_desrialize_bst, test_5)
{
    std::println("{}", Codec::serialize(Codec::deserialize("1n")));
}
