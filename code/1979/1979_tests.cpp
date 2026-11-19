#include "1979.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findGCD;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,5,6,9,10] 2
[7,5,6,8,3]  1
[3,3]        3
)");

using t1979 = SolutionTests<Solution>;

TEST_P(t1979, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findGCD(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1979,
    t1979::parameters(kCases.size()),
    t1979::name);
