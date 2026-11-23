#include <gtest/gtest.h>

#include "2257.hpp"

TEST(CountUnguarded, ReusesBufferAcrossWordBoundaries)
{
    std::vector<std::vector<int>> guards{{0, 0}};
    std::vector<std::vector<int>> walls{{0, 65}};
    EXPECT_EQ(Solution::countUnguarded(1, 66, guards, walls), 0u);
    walls.front().back() = 2;
    for (u32 width : {65u, 64u, 63u, 65u})
    {
        EXPECT_EQ(Solution::countUnguarded(1, width, guards, walls), width - 3);
    }
}

TEST(CountUnguarded, IntersectingSightLines)
{
    std::vector<std::vector<int>> guards{{0, 0}, {1, 1}, {2, 3}};
    std::vector<std::vector<int>> walls{{0, 1}, {2, 2}, {1, 4}};
    EXPECT_EQ(Solution::countUnguarded(4, 6, guards, walls), 7u);
}
