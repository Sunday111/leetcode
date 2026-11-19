#include "3775.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::reverseWords;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"cat and mice" "cat dna mice"
)cases");

using t3775 = SolutionTests<Solution>;

TEST_P(t3775, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.reverseWords(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3775,
    t3775::parameters(kCases.size()),
    t3775::name);
