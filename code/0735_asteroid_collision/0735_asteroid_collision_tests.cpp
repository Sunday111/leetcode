#include "0735_asteroid_collision.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::asteroidCollision;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[10,2,-5] [10]

[-2,-1,1,2] [-2,-1,1,2]
)cases");

using t0735_asteroid_collision = SolutionTests<Solution>;

TEST_P(t0735_asteroid_collision, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.asteroidCollision(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0735_asteroid_collision,
    t0735_asteroid_collision::parameters(kCases.size()),
    t0735_asteroid_collision::name);
