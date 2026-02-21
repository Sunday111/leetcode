#include <immintrin.h>

#include <print>

#include "0762_prime_number_of_set_bits_in_binary_representation.hpp"
#include "gtest/gtest.h"

TEST(t0762_prime_number_of_set_bits_in_binary_representation, test_1)
{
    ASSERT_EQ(Solution{}.countPrimeSetBits(6, 10), 4);
    ASSERT_EQ(Solution{}.countPrimeSetBits(10, 15), 5);
    ASSERT_EQ(Solution{}.countPrimeSetBits(990'000, 1'000'000), 3754);
}

TEST(t0762_prime_number_of_set_bits_in_binary_representation, test_2)
{
    u32 p = ~u32{};
    for (u32 x = 0; x != 1000; ++x)
    {
        u32 r = Solution{}.countPrimeSetBits(1, x);
        if (r != p)
        {
            std::println("{}: {}", x, r);
            p = r;
        }
    }

    std::println("Total: {}", Solution{}.countPrimeSetBits(1, 1'000'000));
}
