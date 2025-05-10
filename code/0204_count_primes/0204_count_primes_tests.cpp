#include "0204_count_primes.hpp"
#include "gtest/gtest.h"

TEST(t0204_count_primes, test_1)
{
    EXPECT_EQ(Solution{}.countPrimes(10), 4);
    EXPECT_EQ(Solution{}.countPrimes(0), 0);
    EXPECT_EQ(Solution{}.countPrimes(1), 0);
    EXPECT_EQ(Solution{}.countPrimes(5'000'000), 0);
}
