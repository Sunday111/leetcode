#include "1970_last_day_where_you_can_still_cross.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t1970_last_day_where_you_can_still_cross, test_1)
{
    auto cells = parse2DArray("[[1,1],[2,1],[1,2],[2,2]]");
    ASSERT_EQ(Solution{}.latestDayToCross(2, 2, cells), 2);
}
