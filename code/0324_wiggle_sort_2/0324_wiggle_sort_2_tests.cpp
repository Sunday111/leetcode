#include "0324_wiggle_sort_2.hpp"
#include "gtest/gtest.h"

TEST(t0324_wiggle_sort_2, test_1)
{
    std::vector values{1, 5, 1, 1, 6, 4};
    Solution{}.wiggleSort(values);

    std::vector expected{1, 6, 1, 5, 1, 4};

    ASSERT_EQ(values, expected);
}

TEST(t0324_wiggle_sort_2, test_2)
{
    std::vector values{1, 3, 2, 2, 3, 1};
    Solution{}.wiggleSort(values);

    std::vector expected{2, 3, 1, 3, 1, 2};

    ASSERT_EQ(values, expected);
}
