#include "0761_special_binary_string.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::makeLargestSpecial;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"11011000" "11100100"

"10" "10"

"110110100100" "111010010100"

"11001011101000101100" "11101000110011001010"
)cases");

using t0761_special_binary_string = SolutionTests<Solution>;

TEST_P(t0761_special_binary_string, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.makeLargestSpecial(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0761_special_binary_string,
    t0761_special_binary_string::parameters(kCases.size()),
    t0761_special_binary_string::name);
