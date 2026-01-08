#include "1458_max_dot_product_of_two_sequences.hpp"
#include "gtest/gtest.h"

TEST(t1458_max_dot_product_of_two_sequences, test_1)
{
    std::vector<int> a{2, 1, -2, 5};
    std::vector<int> b{3, 0, -6};
    ASSERT_EQ(Solution{}.maxDotProduct(a, b), 18);
}

TEST(t1458_max_dot_product_of_two_sequences, test_2)
{
    std::vector<int> a{3, -2};
    std::vector<int> b{2, -6, 7};
    ASSERT_EQ(Solution{}.maxDotProduct(a, b), 21);
}

TEST(t1458_max_dot_product_of_two_sequences, test_3)
{
    std::vector<int> a{-1, -1};
    std::vector<int> b{1, 1};
    ASSERT_EQ(Solution{}.maxDotProduct(a, b), -1);
}

TEST(t1458_max_dot_product_of_two_sequences, test_4)
{
    std::vector<int> a{-3, -8, 3, -10, 1, 3};
    std::vector<int> b{9, 2, 3, 7, -9, 1, 5};
    ASSERT_EQ(Solution{}.maxDotProduct(a, b), 133);
}

TEST(t1458_max_dot_product_of_two_sequences, test_5)
{
    std::vector<int> a{-3, -8, 3, -10, 1, 3, 9};
    std::vector<int> b{9, 2, 3, 7, -9, 1, -8, 5, -1, -1};
    ASSERT_EQ(Solution{}.maxDotProduct(a, b), 200);
}

TEST(t1458_max_dot_product_of_two_sequences, test_6)
{
    std::vector<int> a{-3, -8, -10};
    std::vector<int> b{7, -9, -8};
    ASSERT_EQ(Solution{}.maxDotProduct(a, b), 152);
}
