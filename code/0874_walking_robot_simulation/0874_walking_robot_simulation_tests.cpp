#include "0874_walking_robot_simulation.hpp"
#include "gtest/gtest.h"

TEST(t0874_walking_robot_simulation, test_1)
{
    std::vector<int> commands{4, -1, 4, -2, 4};
    std::vector<std::vector<int>> obstacles{{2, 4}};
    int expected = 65;
    int actual = Solution{}.robotSim(commands, obstacles);
    ASSERT_EQ(expected, actual);
}

TEST(t0874_walking_robot_simulation, test_2)
{
    std::vector<int> commands{-2, -1, 8, 9, 6};
    std::vector<std::vector<int>> obstacles{
        {-1, 3},
        {0, 1},
        {-1, 5},
        {-2, -4},
        {5, 4},
        {-2, -3},
        {5, -1},
        {1, -1},
        {5, 5},
        {5, 2},
    };
    int expected = 0;
    int actual = Solution{}.robotSim(commands, obstacles);
    ASSERT_EQ(expected, actual);
}

TEST(t0874_walking_robot_simulation, test_3)
{
    std::vector<int> commands{-2, 8, 3, 7, -1};
    std::vector<std::vector<int>> obstacles{
        {-4, -1},
        {1, -1},
        {1, 4},
        {5, 0},
        {4, 5},
        {-2, -1},
        {2, -5},
        {5, 1},
        {-3, -1},
        {5, -3},
    };
    int expected = 324;
    int actual = Solution{}.robotSim(commands, obstacles);
    ASSERT_EQ(expected, actual);
}

TEST(t0874_walking_robot_simulation, test_4)
{
    std::vector<int> commands{7, -2, -2, 7, 5};
    std::vector<std::vector<int>> obstacles{
        {-3, 2},
        {-2, 1},
        {0, 1},
        {-2, 4},
        {-1, 0},
        {-2, -3},
        {0, -3},
        {4, 4},
        {-3, 3},
        {2, 2},
    };
    int expected = 4;
    int actual = Solution{}.robotSim(commands, obstacles);
    ASSERT_EQ(expected, actual);
}
