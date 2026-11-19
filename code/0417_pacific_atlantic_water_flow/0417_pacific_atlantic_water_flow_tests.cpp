#include <print>

#include "0417_pacific_atlantic_water_flow.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

static constexpr auto kMethodToTest = &Solution::pacificAtlantic;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
[[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
)cases");

using t0417_pacific_atlantic_water_flow = SolutionTests<Solution>;

TEST_P(t0417_pacific_atlantic_water_flow, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args)
                { return solution.pacificAtlantic(args...); },
                inputs);
            std::ranges::sort(actual);
            ASSERT_EQ(expected, actual);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0417_pacific_atlantic_water_flow,
    t0417_pacific_atlantic_water_flow::parameters(kCases.size()),
    t0417_pacific_atlantic_water_flow::name);
