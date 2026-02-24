#include "1079_letter_tile_possibilities.hpp"
#include "gtest/gtest.h"

TEST(t1079_letter_tile_possibilities, test_1)
{
    ASSERT_EQ(Solution{}.numTilePossibilities("AAB"), 8);
}

TEST(t1079_letter_tile_possibilities, test_2)
{
    ASSERT_EQ(Solution{}.numTilePossibilities("AAABBC"), 188);
}

TEST(t1079_letter_tile_possibilities, test_3)
{
    ASSERT_EQ(Solution{}.numTilePossibilities("V"), 1);
}
