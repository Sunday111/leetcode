#include "2761_prime_pairs_with_target_sum.hpp"
#include "gtest/gtest.h"

TEST(t2761_prime_pairs_with_target_sum, test_1)
{
    std::vector<std::vector<int>> expected = {{3, 7}, {5, 5}};
    auto actual = Solution{}.findPrimePairs(10);
    ASSERT_EQ(actual, expected);
}

TEST(t2761_prime_pairs_with_target_sum, test_2)
{
    std::vector<std::vector<int>> expected = {};
    auto actual = Solution{}.findPrimePairs(2);
    ASSERT_EQ(actual, expected);
}

TEST(t2761_prime_pairs_with_target_sum, test_3)
{
    std::vector<std::vector<int>> expected =
        {{3, 97}, {11, 89}, {17, 83}, {29, 71}, {41, 59}, {47, 53}};
    auto actual = Solution{}.findPrimePairs(100);
    ASSERT_EQ(actual, expected);
}
