#include "0046_permutationstest_cases.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

using t0046_permutations = SolutionTests<Solution>;

TEST_P(t0046_permutations, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.permute(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0046_permutations,
    t0046_permutations::parameters(kCases.size()),
    t0046_permutations::name);
