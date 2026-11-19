#include "2333.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minSumSquareDiff;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(

[1,4,10,12]
[5,8,6,9]
1
1
43

[1,2,3,4]
[2,10,20,19]
0
0
579
)");

using t2333 = SolutionTests<Solution>;

TEST_P(t2333, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minSumSquareDiff(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2333,
    t2333::parameters(kCases.size()),
    t2333::name);
