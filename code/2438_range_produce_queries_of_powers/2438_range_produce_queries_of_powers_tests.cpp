#include "2438_range_produce_queries_of_powers.hpp"
#include "gtest/gtest.h"

TEST(t2438_range_produce_queries_of_powers, test_1)
{
    std::vector<int> expected{10};
    std::vector<std::vector<int>> queries{
        {{5, 5}, {4, 4}, {0, 1}, {1, 5}, {4, 6}, {6, 6}, {5, 6}, {0, 3},
         {5, 5}, {5, 6}, {1, 2}, {3, 5}, {3, 6}, {5, 5}, {4, 4}, {1, 1},
         {2, 4}, {4, 5}, {4, 4}, {5, 6}, {0, 4}, {3, 3}, {0, 4}, {0, 5},
         {4, 4}, {5, 5}, {4, 6}, {4, 5}, {0, 4}, {6, 6}, {6, 6}, {6, 6},
         {2, 2}, {0, 5}, {1, 4}, {0, 3}, {2, 4}, {5, 5}, {6, 6}, {2, 2},
         {2, 3}, {5, 5}, {0, 6}, {3, 3}, {6, 6}, {4, 4}, {0, 0}, {0, 2},
         {6, 6}, {6, 6}, {3, 6}, {0, 4}, {6, 6}, {2, 2}, {4, 6}}};
    ASSERT_EQ(Solution{}.productQueries(919, queries), expected);
}
