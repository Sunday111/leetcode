#include "0046.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::permute;

inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3]
[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

[0,1]
[[0,1],[1,0]]

[1]
[[1]]
)");

using t0046 = SolutionTests<Solution>;

TEST_P(t0046, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.permute(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0046,
    t0046::parameters(kCases.size()),
    t0046::name);
