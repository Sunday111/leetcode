#include "1347_test_cases.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

using t1347_minimum_number_of_steps_to_make_two_strings_anagram =
    SolutionTests<Solution>;

TEST_P(t1347_minimum_number_of_steps_to_make_two_strings_anagram, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minSteps(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1347_minimum_number_of_steps_to_make_two_strings_anagram,
    t1347_minimum_number_of_steps_to_make_two_strings_anagram::parameters(
        kCases.size()),
    t1347_minimum_number_of_steps_to_make_two_strings_anagram::name);
