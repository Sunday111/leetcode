#include "3337_total_characters_in_string_after_transformations_2.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::lengthAfterTransformations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcyy" 2 [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2] 7

"azbk" 1 [2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2] 8

"abcyrsmtfyjhnvhvrtmhvvngvmkempcvepbgxxbeebyhy"
999
[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2]
869688536
)cases");

using t3337_total_characters_in_string_after_transformations_2 =
    SolutionTests<Solution>;

TEST_P(t3337_total_characters_in_string_after_transformations_2, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.lengthAfterTransformations(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3337_total_characters_in_string_after_transformations_2,
    t3337_total_characters_in_string_after_transformations_2::parameters(
        kCases.size()),
    t3337_total_characters_in_string_after_transformations_2::name);
