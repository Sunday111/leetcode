#include "0966.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::spellchecker;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["KiTe","kite","hare","Hare"]
["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
)cases");

using t0966 = SolutionTests<Solution>;

TEST_P(t0966, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.spellchecker(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0966,
    t0966::parameters(kCases.size()),
    t0966::name);
