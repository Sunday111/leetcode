#include "1900_the_earliest_and_latest_rounds_where_players_compete.hpp"
#include "gtest/gtest.h"

TEST(t1900_the_earliest_and_latest_rounds_where_players_compete, test_1)
{
    std::vector<int> expected{3, 4};
    ASSERT_EQ(Solution{}.earliestAndLatest(11, 2, 4), expected);
}

TEST(t1900_the_earliest_and_latest_rounds_where_players_compete, test_2)
{
    std::vector<int> expected{1, 1};
    ASSERT_EQ(Solution{}.earliestAndLatest(5, 1, 5), expected);
}
