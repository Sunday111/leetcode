#include "0417_pacific_atlantic_water_flow.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_utility.hpp"

TEST(t0417_pacific_atlantic_water_flow, test_1)
{
    auto str =
        "["
        "[1,2,2,3,5],"
        "[3,2,3,4,4],"
        "[2,4,5,3,1],"
        "[6,7,1,4,5],"
        "[5,1,1,2,4]]";
    auto hmap = parse2DArray(str);
    for (auto& row : hmap)
    {
        std::println("{}", row);
    }
    auto expected = parse2DArray("[[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]");
    auto actual = Solution{}.pacificAtlantic(hmap);
    ASSERT_EQ(sorted(actual), sorted(expected));
}
