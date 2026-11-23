#include "3411.hpp"
#include "3411_2.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxLength;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,1,2,1,1,1]
5

[2,3,4,5,6]
3

[1,2,3,1,4,5,1]
5


)");

using t3411 = SolutionTests<Solution, Solution_2>;

TEST_P(t3411, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxLength(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3411,
    t3411::parameters(kCases.size()),
    t3411::name);
