#include "1352.hpp"
#include "gtest/gtest.h"

TEST(t1352, Example)
{
    ProductOfNumbers instance;
    instance.add(3);
    instance.add(0);
    instance.add(2);
    instance.add(5);
    instance.add(4);
    EXPECT_EQ(instance.getProduct(2), 20);
    EXPECT_EQ(instance.getProduct(3), 40);
    EXPECT_EQ(instance.getProduct(4), 0);
    instance.add(8);
    EXPECT_EQ(instance.getProduct(2), 32);
}
