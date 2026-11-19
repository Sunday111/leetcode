#include "1345.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minJumps;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[100,-23,-23,404,100,23,23,23,3,404]    3
[7]                                     0
[7,6,9,6,9,6,9,7]                       1
)");

using t1345 = SolutionTests<Solution>;

TEST_P(t1345, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minJumps(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1345,
    t1345::parameters(kCases.size()),
    t1345::name);
