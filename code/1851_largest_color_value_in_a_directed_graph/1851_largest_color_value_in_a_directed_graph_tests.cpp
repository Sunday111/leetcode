#include "1851_largest_color_value_in_a_directed_graph.hpp"
#include "gtest/gtest.h"

TEST(t1851_largest_color_value_in_a_directed_graph, test_1)
{
    std::string colors = "abaca";
    std::vector<std::vector<int>> edges{{0, 1}, {0, 2}, {2, 3}, {3, 4}};
    constexpr int expected = 3;
    const int actual = Solution{}.largestPathValue(colors, edges);
    ASSERT_EQ(expected, actual);
}

TEST(t1851_largest_color_value_in_a_directed_graph, test_2)
{
    std::string colors = "a";
    std::vector<std::vector<int>> edges{{0, 0}};
    constexpr int expected = -1;
    const int actual = Solution{}.largestPathValue(colors, edges);
    ASSERT_EQ(expected, actual);
}

TEST(t1851_largest_color_value_in_a_directed_graph, test_3)
{
    std::string colors = "hhqhuqhqff";
    std::vector<std::vector<int>> edges{
        {0, 1},
        {0, 2},
        {2, 3},
        {3, 4},
        {3, 5},
        {5, 6},
        {2, 7},
        {6, 7},
        {7, 8},
        {3, 8},
        {5, 8},
        {8, 9},
        {3, 9},
        {6, 9},
    };
    constexpr int expected = 3;
    const int actual = Solution{}.largestPathValue(colors, edges);
    ASSERT_EQ(expected, actual);
}
