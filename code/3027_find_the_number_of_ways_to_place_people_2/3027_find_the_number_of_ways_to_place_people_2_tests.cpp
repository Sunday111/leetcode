#include "3027_find_the_number_of_ways_to_place_people_2.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t3025_find_the_number_of_ways_to_place_people_1, test_1)
{
    ASSERT_EQ(
        Solution{}.numberOfPairs(parse2DArray("[[2,5],[128653,-2370425]]")),
        1);
}
