#include "0874_walking_robot_simulation.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::robotSim;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[4,-1,4,-2,4] [[2,4]] 65

[-2,-1,8,9,6] [[-1,3],[0,1],[-1,5],[-2,-4],[5,4],[-2,-3],[5,-1],[1,-1],[5,5],[5,2]] 0

[-2,8,3,7,-1] [[-4,-1],[1,-1],[1,4],[5,0],[4,5],[-2,-1],[2,-5],[5,1],[-3,-1],[5,-3]] 324

[7,-2,-2,7,5] [[-3,2],[-2,1],[0,1],[-2,4],[-1,0],[-2,-3],[0,-3],[4,4],[-3,3],[2,2]] 4
)cases");

class t0874_walking_robot_simulation : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0874_walking_robot_simulation, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.robotSim(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0874_walking_robot_simulation,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
