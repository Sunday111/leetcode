
#include "1488_avoid_flood_in_the_city.hpp"
#include "gtest/gtest.h"

void test(const std::vector<int>& rains)
{
    auto cpy = rains;
    auto ans = Solution{}.avoidFlood(cpy);

    std::unordered_map<int, u32> flooded;
    for (u32 day = 0; day != rains.size(); ++day)
    {
        int lake = rains[day];
        if (lake)
        {
            ASSERT_FALSE(flooded.contains(lake));
            flooded.emplace(lake, day);
        }
        else
        {
            int to_dry = ans[day];
            if (flooded.contains(to_dry))
            {
                ASSERT_GT(day, flooded[to_dry]);
                flooded.erase(to_dry);
            }
        }
    }
}

TEST(t1488_avoid_flood_in_the_city, test_1)
{
    std::vector<int> rains{1, 2, 3, 4};
    std::vector<int> ans{-1, -1, -1, -1};
    ASSERT_EQ(Solution{}.avoidFlood(rains), ans);
}

TEST(t1488_avoid_flood_in_the_city, test_2)
{
    std::vector<int> rains{
        24526, 23938, 93949, 0,     61370, 0,     0,     80971, 0,     0,
        0,     55547, 0,     80482, 74942, 77698, 54795, 0,     0,     0,
        0,     77698, 0,     0,     54410, 0,     0,     23938, 0,     0,
        0,     0,     0,     0,     75018, 0,     0,     47564, 0,     24526,
        0,     0,     0,     48639, 0,     68554, 39045, 75357, 48639, 6992,
        0,     47564, 54410, 0,     0,     0,     74942, 6992,  40783, 82220,
        0,     75018, 0,     61370, 0,     0,     68554, 0,     0,     82220,
        0,     40783, 55547, 80971, 0,     93949, 87360, 0,     87360, 39045,
        0,     80482, 75357, 0,     0,     54795};
    test(rains);
}
