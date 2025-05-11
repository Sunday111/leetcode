#include "0313_super_ugly_number.hpp"
#include "gtest/gtest.h"

TEST(t0313_super_ugly_number, test_1)
{
    std::vector<int32_t> primes{2, 3, 5};
    EXPECT_EQ(Solution{}.nthSuperUglyNumber(10, primes), 12);
    EXPECT_EQ(Solution{}.nthSuperUglyNumber(1690, primes), 2123366400);
}
