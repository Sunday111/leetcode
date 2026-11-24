#include <print>

#include "bitsets/next_with_x_popcount.hpp"
#include "gtest/gtest.h"

static_assert(next_with_x_popcount(1, 1) == 1);
static_assert(next_with_x_popcount(0b1001001, 4) == 0b1001011);
static_assert(next_with_x_popcount(0b1001011, 3) == 0b1001100);
static_assert(next_with_x_popcount(0b10011100, 2) == 0b10100000);

[[gnu::target("bmi2")]] u32 wrap(u32 v, u8 x)
{
    return next_with_x_popcount(v, x);
}

TEST(next_with_x_popcount, test_next_with_x_popcount)
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
            ASSERT_EQ(brute_force(v, x), wrap(v, x));
        }
    }
}
