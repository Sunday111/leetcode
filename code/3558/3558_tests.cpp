#include "3558.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::assignEdgeWeights;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2]]
1

[[1,2],[1,3],[3,4],[3,5]]
2


)");

using t3558 = SolutionTests<Solution>;

TEST_P(t3558, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.assignEdgeWeights(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3558,
    t3558::parameters(kCases.size()),
    t3558::name);
