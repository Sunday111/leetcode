#include "2434.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::robotWithString;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"zza" "azz"

"bac" "abc"

"bdda" "addb"

"bydizfve" "bdevfziy"

"bzeyxf" "befxyz"

"vzhofnpo" "fnohopzv"

"mmuqezwmomeplrtskz" "eekstrlpmomwzqummz"
)cases");

using t2434_using_a_robot_to_print_the_lexicographically_smallest_string =
    SolutionTests<Solution>;

TEST_P(t2434_using_a_robot_to_print_the_lexicographically_smallest_string, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.robotWithString(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2434_using_a_robot_to_print_the_lexicographically_smallest_string,
    t2434_using_a_robot_to_print_the_lexicographically_smallest_string::
        parameters(kCases.size()),
    t2434_using_a_robot_to_print_the_lexicographically_smallest_string::name);
