#include "3842_toggle_light_bulbs.hpp"
#include "gtest/gtest.h"

TEST(t3842_toggle_light_bulbs, test_1)
{
    std::vector x{10, 30, 20, 10};
    std::vector expected{20, 30};
    ASSERT_EQ(Solution{}.toggleLightBulbs(x), expected);
}

TEST(t3842_toggle_light_bulbs, test_2)
{
    std::vector x{100, 100};
    std::vector<int> expected{};
    ASSERT_EQ(Solution{}.toggleLightBulbs(x), expected);
}
