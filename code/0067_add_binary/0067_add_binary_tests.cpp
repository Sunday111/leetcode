#include "0067_add_binary.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::addBinary;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"11" "1" "100"

"1010" "1011" "10101"
)cases");

using t0067_add_binary = SolutionTests<Solution>;

TEST_P(t0067_add_binary, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.addBinary(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0067_add_binary,
    t0067_add_binary::parameters(kCases.size()),
    t0067_add_binary::name);
