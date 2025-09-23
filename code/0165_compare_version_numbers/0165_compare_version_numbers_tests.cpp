#include "0165_compare_version_numbers.hpp"
#include "gtest/gtest.h"

TEST(t0165_compare_version_numbers, test_1)
{
    ASSERT_EQ(Solution{}.compareVersion("1.2", "1.10"), -1);
}

TEST(t0165_compare_version_numbers, test_2)
{
    ASSERT_EQ(Solution{}.compareVersion("1.0.1", "1"), 1);
}
