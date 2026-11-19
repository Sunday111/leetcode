#include "1301.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::pathsWithMaxScore;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
["E23","2X2","12S"] [7,1]
["E12","1X1","21S"] [4,2]
["E11","XXX","11S"] [0,0]
)");

using t1301 = SolutionTests<Solution>;

TEST_P(t1301, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.pathsWithMaxScore(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1301,
    t1301::parameters(kCases.size()),
    t1301::name);
