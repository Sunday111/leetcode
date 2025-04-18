#include "0297_srialize_and_desrialize_binary_tree.hpp"
#include "gtest/gtest.h"

TEST(t0297_srialize_and_desrialize_binary_tree, test_1)
{
    Codec codec;

    std::println("{}", codec.serialize(codec.deserialize("1,2,3,2x,4,5")));
}

TEST(t0297_srialize_and_desrialize_binary_tree, test_2)
{
    Codec codec;

    std::println("{}", codec.serialize(codec.deserialize("")));
}

TEST(t0297_srialize_and_desrialize_binary_tree, test_3)
{
    Codec codec;

    std::println("{}", codec.serialize(codec.deserialize("1,2,-13,2x,4,5")));
}

TEST(t0297_srialize_and_desrialize_binary_tree, test_4)
{
    Codec codec;

    std::println("{}", codec.serialize(codec.deserialize("1,2")));
}
