#include "3275_kth_nearest_obstacle.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t3275_kth_nearest_obstacle, test_scan_int)
{
    ASSERT_EQ(-22, parse_from_string<int>("-22"));
}

TEST(t3275_kth_nearest_obstacle, test_scan_vector)
{
    std::vector expected{1, 2, 3};
    ASSERT_EQ(expected, parse_from_string<std::vector<int>>("[1,2,3]"));
}

TEST(t3275_kth_nearest_obstacle, test_scan_vector_vector)
{
    std::vector<std::vector<int>> expected{{1, 2, 3}, {4, 5, 6}};
    ASSERT_EQ(
        expected,
        parse_from_string<std::vector<std::vector<int>>>("[[1,2,3],[4,5,6]]"));
}

TEST(t3275_kth_nearest_obstacle, test_scan_tuple)
{
    auto expected = std::make_tuple(10, std::vector{1, 2, 3});
    auto actual =
        parse_from_string<std::tuple<int, std::vector<int>>>("10[1,2,3]");
    ASSERT_EQ(expected, actual);
}

TEST(t3275_kth_nearest_obstacle, test_1)
{
    auto q = parse2DArray("[[1,2],[3,4],[2,3],[-3,0]]");
    const std::vector expected{-1, 7, 5, 3};
    ASSERT_EQ(Solution{}.resultsArray(q, 2), expected);
}
