#include "3217.hpp"
#include "gtest/gtest.h"

TEST(t3217, ClearsMembershipBetweenCalls)
{
    ListNode tail{100'000};
    ListNode middle{64, &tail};
    ListNode head{63, &middle};

    EXPECT_EQ(Solution::modifiedList({63, 100'000}, &head), &middle);
    EXPECT_EQ(middle.next, nullptr);

    head.next = &middle;
    middle.next = &tail;
    EXPECT_EQ(Solution::modifiedList({64}, &head), &head);
    EXPECT_EQ(head.next, &tail);
    EXPECT_EQ(tail.next, nullptr);
}
