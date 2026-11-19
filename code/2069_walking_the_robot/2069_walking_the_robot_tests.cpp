#include "2069_walking_the_robot.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<size_t, size_t, std::vector<size_t>>,
    std::vector<std::tuple<std::vector<int>, std::string>>>(R"cases(
2 2 [10] [[1,1] "North"]
2 2 [0,4,1] [[0,0] "East", [0,0] "South", [1,0] "East"]
)cases");

class t2069_walking_the_robot : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t2069_walking_the_robot, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [width, height, steps] = inputs;
    Robot robot(width, height);
    ASSERT_EQ(steps.size(), expected.size());
    for (size_t i = 0; i < steps.size(); ++i)
    {
        robot.step(steps[i]);
        auto& [position, direction] = expected[i];
        ASSERT_EQ(robot.getPos(), position);
        ASSERT_EQ(robot.getDir(), direction);
    }
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2069_walking_the_robot,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
