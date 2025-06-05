#include "3355_zero_array_transformations_1.hpp"
#include "gtest/gtest.h"

TEST(t3355_zero_array_transformations_1, test_1)
{
    std::vector nums{1, 0, 1};
    std::vector<std::vector<int>> queries{{0, 2}};
    ASSERT_TRUE(Solution{}.isZeroArray(nums, queries));
}

TEST(t3355_zero_array_transformations_1, test_2)
{
    std::vector nums{4, 6};
    std::vector<std::vector<int>> queries{
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 1},
        {0, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
    };
    ASSERT_TRUE(Solution{}.isZeroArray(nums, queries));
}

TEST(t3355_zero_array_transformations_1, test_3)
{
    std::vector nums{0, 3, 9};
    std::vector<std::vector<int>> queries{
        {0, 2},
        {0, 2},
        {1, 1},
        {1, 2},
        {1, 2},
        {2, 2},
    };
    ASSERT_FALSE(Solution{}.isZeroArray(nums, queries));
}

TEST(t3355_zero_array_transformations_1, test_4)
{
    std::vector nums{1, 1, 3};
    std::vector<std::vector<int>> queries{
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 1},
        {0, 2},
        {0, 2},
        {1, 1},
        {1, 1},
        {1, 1},
        {1, 1},
        {2, 2},
        {2, 2},
    };
    ASSERT_TRUE(Solution{}.isZeroArray(nums, queries));
}
