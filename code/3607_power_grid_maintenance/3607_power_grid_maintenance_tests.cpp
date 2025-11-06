#include "3607_power_grid_maintenance.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t3607_power_grid_maintenance, test_1)
{
    u32 c = 5;
    auto connections = parse2DArray("[[1,2],[2,3],[3,4],[4,5]]");
    auto queries = parse2DArray("[[1,3],[2,1],[1,1],[2,2],[1,2]]");
    std::vector<int> expected{3, 2, 3};
    ASSERT_EQ(Solution{}.processQueries(c, connections, queries), expected);
}
