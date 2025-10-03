#include "0407_trapping_rain_water.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t0407_trapping_rain_water, test_1)
{
    auto str =
        "[[1,4,3,1,3,2],"
        "[3,2,1,3,2,4],"
        "[2,3,3,2,3,1]]";
    auto hmap = parse2DArray(str);
    for (auto& row : hmap)
    {
        std::println("{}", row);
    }
    ASSERT_EQ(Solution{}.trapRainWater(hmap), 4);
}
