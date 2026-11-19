#include "1386.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxNumberOfFamilies;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
3 [[1,2],[1,3],[1,8],[2,6],[3,1],[3,10]]    4
2 [[2,1],[1,8],[2,6]]                       2
4 [[4,3],[1,4],[4,6],[1,7]]                 4
)");

using t1386 = SolutionTests<Solution>;

TEST_P(t1386, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxNumberOfFamilies(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1386,
    t1386::parameters(kCases.size()),
    t1386::name);
