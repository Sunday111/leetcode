#include "0297_srialize_and_desrialize_binary_tree.hpp"
#include "gtest/gtest.h"

TEST(t0297_srialize_and_desrialize_binary_tree, test_1)
{
    Codec codec;

    std::println("{}", codec.serialize(codec.deserialize("1b,2n,3b,4n,5n")));
}

TEST(t0297_srialize_and_desrialize_binary_tree, test_2)
{
    Codec codec;

    std::println("{}", codec.serialize(codec.deserialize("")));
}

TEST(t0297_srialize_and_desrialize_binary_tree, test_3)
{
    Codec codec;

    std::println("{}", codec.serialize(codec.deserialize("1b,2n,-13b,4n,5n")));
}

TEST(t0297_srialize_and_desrialize_binary_tree, test_4)
{
    Codec codec;

    std::println("{}", codec.serialize(codec.deserialize("1l,2n")));
}

TEST(t0297_srialize_and_desrialize_binary_tree, test_5)
{
    Codec codec;

    std::println("{}", codec.serialize(codec.deserialize("1n")));
}
