#include <unordered_set>

#include "1488_avoid_flood_in_the_city.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, bool>(R"cases(
[1,2,3,4] true
[1,2,0,0,2,1] true
[1,2,0,1,2] false
)cases");

class t1488_avoid_flood_in_the_city : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t1488_avoid_flood_in_the_city, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [rains] = inputs;
    auto working = rains;
    auto actual = Solution{}.avoidFlood(working);
    ASSERT_EQ(!actual.empty(), expected);
    if (!expected) return;
    ASSERT_EQ(actual.size(), rains.size());
    std::unordered_set<int> full;
    for (size_t i = 0; i < rains.size(); ++i)
    {
        if (rains[i])
        {
            ASSERT_EQ(actual[i], -1);
            ASSERT_TRUE(full.insert(rains[i]).second);
        }
        else
        {
            ASSERT_GT(actual[i], 0);
            full.erase(actual[i]);
        }
    }
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1488_avoid_flood_in_the_city,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
