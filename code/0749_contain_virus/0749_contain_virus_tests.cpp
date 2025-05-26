#include "0749_contain_virus.hpp"
#include "gtest/gtest.h"

TEST(t0749_contain_virus, test_1)
{
    std::vector<std::vector<int>> board{
        {0, 1, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_EQ(Solution{}.containVirus(board), 10);
}

TEST(t0749_contain_virus, test_2)
{
    std::vector<std::vector<int>> board{
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1},
    };

    ASSERT_EQ(Solution{}.containVirus(board), 4);
}

TEST(t0749_contain_virus, test_3)
{
    std::vector<std::vector<int>> board{
        {1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0},
    };

    ASSERT_EQ(Solution{}.containVirus(board), 13);
}

TEST(t0749_contain_virus, test_4)
{
    std::vector<std::vector<int>> board{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    ASSERT_EQ(Solution{}.containVirus(board), 56);
}

TEST(t0749_contain_virus, test_5)
{
    std::vector<std::vector<int>> board{
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0, 1, 0},
        {0, 0, 0, 1, 1, 0, 0, 1, 1, 0},
        {0, 1, 0, 0, 1, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 0, 1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1, 0, 0, 1, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 0, 1}};

    ASSERT_EQ(Solution{}.containVirus(board), 38);
}
