#include "2975_maximum_square_area_by_removing_fences_from_a_field.hpp"
#include "gtest/gtest.h"

TEST(t2975_maximum_square_area_by_removing_fences_from_a_field, test_1)
{
    u32 h = 4, w = 3;
    std::vector hFences{2, 3}, vFences{2};
    u32 expected = 4;
    ASSERT_EQ(Solution{}.maximizeSquareArea(h, w, hFences, vFences), expected);
}
