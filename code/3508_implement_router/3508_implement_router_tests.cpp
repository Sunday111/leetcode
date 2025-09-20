#include "3508_implement_router.hpp"
#include "gtest/gtest.h"

TEST(t3508_implement_router, test_1)
{
    Router s(3);
    ASSERT_TRUE(s.addPacket(1, 4, 90));
    ASSERT_TRUE(s.addPacket(2, 5, 90));
    ASSERT_FALSE(s.addPacket(1, 4, 90));
    ASSERT_TRUE(s.addPacket(3, 5, 95));
    ASSERT_TRUE(s.addPacket(4, 5, 105));
}
