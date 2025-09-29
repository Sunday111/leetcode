#include "1039_minimum_score_triangulation_of_polygon.hpp"
#include "gtest/gtest.h"

// TEST(t1039_minimum_score_triangulation_of_polygon, test_1)
// {
//     std::vector<int> values{3, 7, 4, 5};
//     ASSERT_EQ(Solution{}.minScoreTriangulation(values), 144);
// }

TEST(t1039_minimum_score_triangulation_of_polygon, test_2)
{
    std::vector<int> values{1, 3, 1, 4, 1, 5};
    ASSERT_EQ(Solution{}.minScoreTriangulation(values), 13);
}

// TEST(t1039_minimum_score_triangulation_of_polygon, test_3)
// {
//     std::vector<int> values{1, 5, 1, 2, 5};
//     ASSERT_EQ(Solution{}.minScoreTriangulation(values), 17);
// }
