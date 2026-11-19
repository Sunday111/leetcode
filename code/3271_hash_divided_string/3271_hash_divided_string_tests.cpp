#include "3271_hash_divided_string.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::stringHash;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcd" 2 "bf"

"mxz" 3 "i"

"hcr" 3 "a"
)cases");

using t3271_hash_divided_string = SolutionTests<Solution>;

TEST_P(t3271_hash_divided_string, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.stringHash(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3271_hash_divided_string,
    t3271_hash_divided_string::parameters(kCases.size()),
    t3271_hash_divided_string::name);
