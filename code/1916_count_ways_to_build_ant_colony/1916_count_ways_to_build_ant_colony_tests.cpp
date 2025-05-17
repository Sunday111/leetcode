#include "1916_count_ways_to_build_ant_colony.hpp"
#include "gtest/gtest.h"

TEST(t1916_count_ways_to_build_ant_colony, test_1)
{
    std::vector<int32_t> input{-1, 0, 1};
    int32_t expected = 1;
    Solution s{};
    ASSERT_EQ(s.waysToBuildRooms(input), expected);
}

TEST(t1916_count_ways_to_build_ant_colony, test_2)
{
    std::vector<int32_t> input{-1, 0, 0, 1, 2};
    int32_t expected = 6;
    Solution s{};
    ASSERT_EQ(s.waysToBuildRooms(input), expected);
}

TEST(t1916_count_ways_to_build_ant_colony, test_3)
{
    std::vector<int32_t> input{-1, 0, 0, 1, 0};
    int32_t expected = 12;
    Solution s{};
    ASSERT_EQ(s.waysToBuildRooms(input), expected);
}

TEST(t1916_count_ways_to_build_ant_colony, test_4)
{
    std::vector<int32_t> input{-1};
    int32_t expected = 1;
    Solution s{};
    ASSERT_EQ(s.waysToBuildRooms(input), expected);
}
