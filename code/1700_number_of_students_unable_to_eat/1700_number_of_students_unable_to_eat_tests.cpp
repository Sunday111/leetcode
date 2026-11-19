#include "1700_number_of_students_unable_to_eat.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countStudents;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,1] [0,1,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0] 3
)cases");

using t1700_number_of_students_unable_to_eat = SolutionTests<Solution>;

TEST_P(t1700_number_of_students_unable_to_eat, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countStudents(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1700_number_of_students_unable_to_eat,
    t1700_number_of_students_unable_to_eat::parameters(kCases.size()),
    t1700_number_of_students_unable_to_eat::name);
