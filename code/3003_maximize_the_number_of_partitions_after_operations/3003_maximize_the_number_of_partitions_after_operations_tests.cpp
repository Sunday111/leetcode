#include "3003_maximize_the_number_of_partitions_after_operations.hpp"
#include "gtest/gtest.h"

TEST(t3003_maximize_the_number_of_partitions_after_operations, test_1)
{
    ASSERT_EQ(Solution{}.maxPartitionsAfterOperations("accca", 2), 3);
}

TEST(t3003_maximize_the_number_of_partitions_after_operations, test_2)
{
    ASSERT_EQ(Solution{}.maxPartitionsAfterOperations("aabaab", 3), 1);
}

TEST(t3003_maximize_the_number_of_partitions_after_operations, test_3)
{
    ASSERT_EQ(Solution{}.maxPartitionsAfterOperations("xxyz", 1), 4);
}

TEST(t3003_maximize_the_number_of_partitions_after_operations, test_4)
{
    std::string s = "bbbbcbcbbc";
    ASSERT_EQ(Solution{}.maxPartitionsAfterOperations(s, 2), 3);
}
