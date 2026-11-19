#include "0029_divide_two_integers.hpp"
#include "0029_divide_two_integers_msb.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<int, int>, int>(R"cases(
10 3 3
7 -3 -2
0 1 0
-2147483648 -1 2147483647
-2147483648 1 -2147483648
-2147483648 -2147483648 1
)cases");

using t0029_divide_two_integers = SolutionTests<Solution, SolutionMSB>;

TEST_P(t0029_divide_two_integers, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args) { return solution.divide(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0029_divide_two_integers,
    t0029_divide_two_integers::parameters(kCases.size()),
    t0029_divide_two_integers::name);
