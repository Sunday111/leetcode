#include <algorithm>

#include "0378_kth_smallest_element_in_a_sorted_matrix.hpp"
#include "gtest/gtest.h"

TEST(t0378_kth_smallest_element_in_a_sorted_matrix, test_1)
{
    std::vector<std::vector<int>> matrix{
        {1, 5, 9},
        {10, 11, 13},
        {12, 13, 15},
    };

    std::vector<int> sorted;
    for (auto& row : matrix)
    {
        sorted.insert_range(sorted.end(), row);
    }

    std::ranges::sort(sorted);

    for (int k = 1; k != 10; ++k)
    {
        int expected = sorted[static_cast<uint32_t>(k - 1)];
        int actual = Solution{}.kthSmallest(matrix, k);
        EXPECT_EQ(expected, actual) << "k = " << k;
    }
}

TEST(t0378_kth_smallest_element_in_a_sorted_matrix, test_2)
{
    std::vector<std::vector<int>> matrix{
        {1, 5, 9},
        {10, 11, 13},
        {12, 13, 15},
    };

    ASSERT_EQ(Solution{}.kthSmallest(matrix, 1), 1);
}
