#include "0017.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

static constexpr auto kMethodToTest = &Solution::letterCombinations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"23" ["ad","ae","af","bd","be","bf","cd","ce","cf"]
)");

using t0017 = SolutionTests<Solution>;

TEST_P(t0017, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args)
                { return solution.letterCombinations(args...); },
                inputs);
            ASSERT_EQ(sorted(expected), sorted(actual));
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0017,
    t0017::parameters(kCases.size()),
    t0017::name);
