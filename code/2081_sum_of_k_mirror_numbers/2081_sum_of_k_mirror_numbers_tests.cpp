#include "2081_sum_of_k_mirror_numbers.hpp"
#include "gtest/gtest.h"

TEST(t2081_sum_of_k_mirror_numbers, test_1)
{
    for (uint8_t k = 2; k != 10; ++k)
    {
        for (uint8_t n = 1; n != 31; ++n)
        {
            ASSERT_EQ(Solution{}.kMirror(k, n), Cheat::kMirror(k, n))
                << "k = " << int{k} << ", n = " << int{n};
        }
    }
}

#ifndef NDEBUG

TEST(t2081_sum_of_k_mirror_numbers, test_2)
{
    for (uint8_t k = 2; k != 10; ++k)
    {
        for (uint8_t n = 1; n != 31; ++n)
        {
            ASSERT_EQ(Solution2{}.kMirror(k, n), Cheat::kMirror(k, n))
                << "k = " << int{k} << ", n = " << int{n};
        }
    }
}

TEST(t2081_sum_of_k_mirror_numbers, test_3)
{
    for (uint8_t k = 2; k != 10; ++k)
    {
        for (uint8_t n = 1; n != 31; ++n)
        {
            ASSERT_EQ(Solution3{}.kMirror(k, n), Cheat::kMirror(k, n))
                << "k = " << int{k} << ", n = " << int{n};
        }
    }
}

TEST(t2081_sum_of_k_mirror_numbers, test_4)
{
    for (uint8_t k = 2; k != 10; ++k)
    {
        for (uint8_t n = 1; n != 31; ++n)
        {
            ASSERT_EQ(Solution4{}.kMirror(k, n), Cheat::kMirror(k, n))
                << "k = " << int{k} << ", n = " << int{n};
        }
    }
}
#endif
