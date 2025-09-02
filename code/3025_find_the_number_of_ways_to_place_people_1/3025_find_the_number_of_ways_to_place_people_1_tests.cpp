#include "3025_find_the_number_of_ways_to_place_people_1.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t3025_find_the_number_of_ways_to_place_people_1, test_1)
{
    ASSERT_EQ(Solution{}.numberOfPairs(parse2DArray("[[0,0],[0,3]]")), 1);
    ASSERT_EQ(Solution{}.numberOfPairs(parse2DArray("[[1,1],[2,2],[3,3]]")), 0);
    ASSERT_EQ(Solution{}.numberOfPairs(parse2DArray("[[3,1],[1,3],[1,1]]")), 2);
}
