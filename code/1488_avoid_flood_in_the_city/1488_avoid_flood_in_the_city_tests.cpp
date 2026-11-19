#include <unordered_set>

#include "1488_avoid_flood_in_the_city.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, bool>(R"cases(
[1,2,3,4] true
[1,2,0,0,2,1] true
[1,2,0,1,2] false
)cases");

using t1488_avoid_flood_in_the_city = SolutionTests<Solution>;
TEST_P(t1488_avoid_flood_in_the_city, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto& [rains] = inputs;
            auto working = rains;
            auto actual = solution.avoidFlood(working);
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
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1488_avoid_flood_in_the_city,
    t1488_avoid_flood_in_the_city::parameters(kCases.size()),
    t1488_avoid_flood_in_the_city::name);
