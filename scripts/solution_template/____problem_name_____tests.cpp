#include "____problem_name____.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

// Select the entry point and add input/output cases below.
inline static constexpr auto kMethodToTest = &Solution::solve;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(

)");

using t____problem_name____ = SolutionTests<Solution>;

TEST_P(t____problem_name____, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args) { return solution.solve(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t____problem_name____,
    t____problem_name____::parameters(kCases.size()),
    t____problem_name____::name);
