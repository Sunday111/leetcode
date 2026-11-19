#include "3559.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::assignEdgeWeights;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2]]
[[1,1],[1,2]]
[0,1]

[[1,2],[1,3],[3,4],[3,5]]
[[1,4],[3,4],[2,5]]
[2,1,4]


)");

using t3559 = SolutionTests<Solution>;

TEST_P(t3559, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.assignEdgeWeights(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3559,
    t3559::parameters(kCases.size()),
    t3559::name);
