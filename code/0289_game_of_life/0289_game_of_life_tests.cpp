#include <print>

#include "0289_game_of_life.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<int>>>,
    std::vector<std::vector<int>>>(R"cases(
[[0,1,0],[0,0,1],[1,1,1],[0,0,0]] [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
)cases");

using t0289_game_of_life = SolutionTests<Solution>;

TEST_P(t0289_game_of_life, Test)
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
    t0289_game_of_life,
    t0289_game_of_life::parameters(kCases.size()),
    t0289_game_of_life::name);
