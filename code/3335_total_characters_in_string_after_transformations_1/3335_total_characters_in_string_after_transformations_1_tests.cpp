#include "3335_total_characters_in_string_after_transformations_1.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::lengthAfterTransformations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcyy" 2 7

"azbk" 5 5
)cases");

using t3335_total_characters_in_string_after_transformations_1 =
    SolutionTests<Solution>;

TEST_P(t3335_total_characters_in_string_after_transformations_1, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.lengthAfterTransformations(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3335_total_characters_in_string_after_transformations_1,
    t3335_total_characters_in_string_after_transformations_1::parameters(
        kCases.size()),
    t3335_total_characters_in_string_after_transformations_1::name);
