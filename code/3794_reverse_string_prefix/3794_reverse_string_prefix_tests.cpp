#include "3794_reverse_string_prefix.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::reversePrefix;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcd" 2 "bacd"
)cases");

using t3794_reverse_string_prefix = SolutionTests<Solution>;

TEST_P(t3794_reverse_string_prefix, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.reversePrefix(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3794_reverse_string_prefix,
    t3794_reverse_string_prefix::parameters(kCases.size()),
    t3794_reverse_string_prefix::name);
