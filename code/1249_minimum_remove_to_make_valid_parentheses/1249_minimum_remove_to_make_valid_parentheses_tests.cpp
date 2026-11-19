#include "1249_minimum_remove_to_make_valid_parentheses.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minRemoveToMakeValid;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"lee(t(c)o)de)" "lee(t(c)o)de"

"a)b(c)d" "ab(c)d"

"))((" ""

"(a(b(c)d)" "a(b(c)d)"
)cases");

using t1249_minimum_remove_to_make_valid_parentheses = SolutionTests<Solution>;

TEST_P(t1249_minimum_remove_to_make_valid_parentheses, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minRemoveToMakeValid(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1249_minimum_remove_to_make_valid_parentheses,
    t1249_minimum_remove_to_make_valid_parentheses::parameters(kCases.size()),
    t1249_minimum_remove_to_make_valid_parentheses::name);
