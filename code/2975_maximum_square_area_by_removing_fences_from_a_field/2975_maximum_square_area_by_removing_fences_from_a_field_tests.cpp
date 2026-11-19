#include "2975_maximum_square_area_by_removing_fences_from_a_field.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<unsigned int, unsigned int, std::vector<int>, std::vector<int>>,
    int>(R"cases(
4 3 [2,3] [2] 4
)cases");

using t2975_maximum_square_area_by_removing_fences_from_a_field =
    SolutionTests<Solution>;

TEST_P(t2975_maximum_square_area_by_removing_fences_from_a_field, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximizeSquareArea(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2975_maximum_square_area_by_removing_fences_from_a_field,
    t2975_maximum_square_area_by_removing_fences_from_a_field::parameters(
        kCases.size()),
    t2975_maximum_square_area_by_removing_fences_from_a_field::name);
