#include "1733_minimum_number_of_people_to_teach.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumTeachings;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 [[2],[1,3],[1,2],[3]] [[1,4],[1,2],[3,4],[2,3]] 2
)cases");

using t1733_minimum_number_of_people_to_teach = SolutionTests<Solution>;

TEST_P(t1733_minimum_number_of_people_to_teach, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumTeachings(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1733_minimum_number_of_people_to_teach,
    t1733_minimum_number_of_people_to_teach::parameters(kCases.size()),
    t1733_minimum_number_of_people_to_teach::name);
