#include "2509_cycle_length_queries_in_a_tree.hpp"
#include "gtest/gtest.h"

TEST(t2509_cycle_length_queries_in_a_tree, test_1)
{
    Solution s{};
    int n = 2;
    std::vector<std::vector<int>> queries{{1, 2}};
    std::vector expected{2};
    ASSERT_EQ(s.cycleLengthQueries(n, queries), expected);
}

TEST(t2509_cycle_length_queries_in_a_tree, test_2)
{
    Solution s{};
    int n = 3;
    std::vector<std::vector<int>> queries{{5, 3}, {4, 7}, {2, 3}};
    std::vector expected{4, 5, 3};
    ASSERT_EQ(s.cycleLengthQueries(n, queries), expected);
}

TEST(t2509_cycle_length_queries_in_a_tree, test_3)
{
    Solution s{};
    int n = 5;
    std::vector<std::vector<int>> queries{
        {17, 21},
        {23, 5},
        {15, 7},
        {3, 21},
        {31, 9},
        {5, 15},
        {11, 2},
        {19, 7},
    };
    std::vector expected{7, 3, 2, 6, 8, 6, 3, 7};
    ASSERT_EQ(s.cycleLengthQueries(n, queries), expected);
}
