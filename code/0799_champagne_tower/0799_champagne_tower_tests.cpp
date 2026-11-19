#include "0799_champagne_tower.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::champagneTower;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 1 1 0

2 1 1 0.5

100000009 33 17 1
)cases");

using t0799_champagne_tower = SolutionTests<Solution>;

TEST_P(t0799_champagne_tower, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args) { return solution.champagneTower(args...); },
                inputs);
            ASSERT_NEAR(expected, actual, 0.001);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0799_champagne_tower,
    t0799_champagne_tower::parameters(kCases.size()),
    t0799_champagne_tower::name);
