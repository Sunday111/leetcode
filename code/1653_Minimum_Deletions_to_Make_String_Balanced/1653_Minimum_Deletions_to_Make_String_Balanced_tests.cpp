#include "1653_Minimum_Deletions_to_Make_String_Balanced.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumDeletions;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"aababbab" 2

"bbaaaaabb" 2
)cases");

using t1653_Minimum_Deletions_to_Make_String_Balanced = SolutionTests<Solution>;

TEST_P(t1653_Minimum_Deletions_to_Make_String_Balanced, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumDeletions(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1653_Minimum_Deletions_to_Make_String_Balanced,
    t1653_Minimum_Deletions_to_Make_String_Balanced::parameters(kCases.size()),
    t1653_Minimum_Deletions_to_Make_String_Balanced::name);
