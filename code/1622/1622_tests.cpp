#include "1622.hpp"
#include "gtest/gtest.h"

TEST(t1622, Test)
{
    Fancy fancy;
    fancy.append(2);  // [] -> [2]
    ASSERT_EQ(fancy.getIndex(0), 2);
    fancy.addAll(3);  // [2+3] -> [5]
    ASSERT_EQ(fancy.getIndex(0), 5);
    fancy.append(7);  // [5, 7]
    ASSERT_EQ(fancy.getIndex(0), 5);
    ASSERT_EQ(fancy.getIndex(1), 7);
    fancy.multAll(2);  // [5*2, 7*2] -> [10, 14]
    ASSERT_EQ(fancy.getIndex(0), 10);
    ASSERT_EQ(fancy.getIndex(1), 14);
    fancy.addAll(3);   // [10+3, 14+3] -> [13, 17]
    fancy.append(10);  // [13, 17, 10]
    fancy.multAll(2);  // [13*2, 17*2, 10*2] -> [26, 34, 20]
    ASSERT_EQ(fancy.getIndex(0), 26);
    ASSERT_EQ(fancy.getIndex(1), 34);
    ASSERT_EQ(fancy.getIndex(2), 20);
}
