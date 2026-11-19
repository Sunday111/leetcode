#include "0693_binary_number_with_alternating_bits.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::hasAlternatingBits;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
5 true

7 false

11 false
)cases");

using t0693_binary_number_with_alternating_bits = SolutionTests<Solution>;

TEST_P(t0693_binary_number_with_alternating_bits, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.hasAlternatingBits(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0693_binary_number_with_alternating_bits,
    t0693_binary_number_with_alternating_bits::parameters(kCases.size()),
    t0693_binary_number_with_alternating_bits::name);
