#include "1557.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::findSmallestSetOfVertices;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
6
[[0,1],[0,2],[2,5],[3,4],[4,2]]
[0,3]

5
[[0,1],[2,1],[3,1],[1,4],[2,4]]
[0,2,3]

)");

using t1557 = SolutionTests<Solution>;

TEST_P(t1557, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findSmallestSetOfVertices(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1557,
    t1557::parameters(kCases.size()),
    t1557::name);
