#include "1390_four_divisors.hpp"
#include "gtest/gtest.h"

TEST(t1390_four_divisors, test_1)
{
    std::vector<int> nums{
        31911,
        85919,
        25557,
        9951,
        3936,
        88317,
        71321,
        74651,
        88416,
        34378,
    };
    ASSERT_EQ(Solution{}.sumFourDivisors(nums), 289182);
}

TEST(t1390_four_divisors, test_2)
{
    auto sf = [](u32 a, u32 b)
    {
        return 1u + a + b + a * b;
    };
    ASSERT_EQ(kResults[31911], 0);
    ASSERT_EQ(kResults[85919], sf(151, 569));
}
