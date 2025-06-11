#include "1860_incremental_memory_leak.hpp"
#include "gtest/gtest.h"

TEST(t1860_incremental_memory_leak, test_1)
{
    std::vector<int> expected{6, 0, 4};
    std::vector<int> actual = Solution::memLeak(8, 11);
    ASSERT_EQ(actual, expected);
}

TEST(t1860_incremental_memory_leak, test_2)
{
    std::vector<int> expected{3, 1, 0};
    std::vector<int> actual = Solution::memLeak(2, 2);
    ASSERT_EQ(actual, expected);
}

TEST(t1860_incremental_memory_leak, test_3)
{
    std::vector<int> expected{92681, 88047, 41707};
    std::vector<int> actual = Solution::memLeak(2147483647, 2147483647);
    ASSERT_EQ(actual, expected);
}
