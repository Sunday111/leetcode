#include "0973_k_closest_points_to_origin.hpp"
#include "gtest/gtest.h"

TEST(t0973_k_closest_points_to_origin, test_1)
{
    Solution s{};
    std::vector<std::vector<int>> in{{1, 3}, {-2, 2}};
    std::vector<std::vector<int>> out{{-2, 2}};
    ASSERT_EQ(s.kClosest(in, 1), out);
}
