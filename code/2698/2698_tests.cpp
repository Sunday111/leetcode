#include "2698_test_cases.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

using t2698_find_the_punishment_number_of_an_integer = SolutionTests<Solution>;

TEST_P(t2698_find_the_punishment_number_of_an_integer, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.punishmentNumber(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2698_find_the_punishment_number_of_an_integer,
    t2698_find_the_punishment_number_of_an_integer::parameters(kCases.size()),
    t2698_find_the_punishment_number_of_an_integer::name);
