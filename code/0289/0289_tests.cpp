#include <print>

#include "0289.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<int>>>,
    std::vector<std::vector<int>>>(R"cases(
[[0,1,0],[0,0,1],[1,1,1],[0,0,0]] [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
)cases");

using t0289 = SolutionTests<Solution>;

TEST_P(t0289, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            std::apply(
                [&](auto&... args) { return solution.gameOfLife(args...); },
                inputs);
            auto& actual = std::get<0>(inputs);
            ASSERT_EQ(expected, actual);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0289,
    t0289::parameters(kCases.size()),
    t0289::name);
