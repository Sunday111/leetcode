#include "3715_sum_of_perfect_ancestors.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t3715_sum_of_perfect_ancestors, test_1)
{
    int n = 3;
    auto edges = parse2DArray("[[0,1],[1,2]]");
    std::vector nums{2, 8, 2};
    ASSERT_EQ(Solution{}.sumOfAncestors(n, edges, nums), 3);
}

TEST(t3715_sum_of_perfect_ancestors, test_2)
{
    int n = 3;
    auto edges = parse2DArray("[[0,1],[0,2]]");
    std::vector nums{1, 2, 4};
    ASSERT_EQ(Solution{}.sumOfAncestors(n, edges, nums), 1);
}

TEST(t3715_sum_of_perfect_ancestors, test_3)
{
    int n = 4;
    auto edges = parse2DArray("[[0,1],[0,2],[1,3]]");
    std::vector nums{1, 2, 9, 4};
    ASSERT_EQ(Solution{}.sumOfAncestors(n, edges, nums), 2);
}
