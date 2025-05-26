#include "0735_asteroid_collision.hpp"
#include "gtest/gtest.h"

TEST(t0735_asteroid_collision, test_1)
{
    std::vector<int> asteroids{10, 2, -5};
    std::vector<int> expected{10};
    std::vector<int> actual = Solution{}.asteroidCollision(asteroids);
    ASSERT_EQ(expected, actual);
}

TEST(t0735_asteroid_collision, test_2)
{
    std::vector<int> asteroids{-2, -1, 1, 2};
    std::vector<int> expected{-2, -1, 1, 2};
    std::vector<int> actual = Solution{}.asteroidCollision(asteroids);
    ASSERT_EQ(expected, actual);
}
