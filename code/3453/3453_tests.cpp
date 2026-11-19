#include "3453.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::separateSquares;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[0,0,2],[1,1,1]] 1.1666641235351562
)cases");

using t3453 = SolutionTests<Solution>;

TEST_P(t3453, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args)
                { return solution.separateSquares(args...); },
                inputs);
            ASSERT_NEAR(expected, actual, 0.00001);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3453,
    t3453::parameters(kCases.size()),
    t3453::name);
