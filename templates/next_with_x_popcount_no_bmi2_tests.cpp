#include "gtest/gtest.h"
#include "next_with_x_popcount_no_bmi2.hpp"

TEST(next_with_x_popcount, test_next_with_x_popcount_no_bmi2)
{
    auto brute_force = [](u32 v, u8 x)
    {
        while (true)
        {
            if (std::popcount(v) == x) return v;
            ++v;
        }

        std::unreachable();
    };

    for (u8 x = 1; x != 10; ++x)
    {
        std::println("x = {}", x);
        for (u32 v = 1; v != 100'000; ++v)
        {
            if (!(v % 100000)) std::println("{}", v / 100000);
            ASSERT_EQ(brute_force(v, x), next_with_x_popcount(v, x));
        }
    }
}
