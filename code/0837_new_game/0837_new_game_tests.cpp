#include "0837_new_game.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::new21Game;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
10 1 10 1.0000000149011612

1 0 1 1
)cases");

using t0837_new_game = SolutionTests<Solution>;

TEST_P(t0837_new_game, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args) { return solution.new21Game(args...); },
                inputs);
            ASSERT_FLOAT_EQ(expected, actual);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0837_new_game,
    t0837_new_game::parameters(kCases.size()),
    t0837_new_game::name);
