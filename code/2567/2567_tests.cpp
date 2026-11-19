#include "2567.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimizeSum;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,4,7,8,5]
3

[1,4,3]
0

[7,7,7]
0

[1,1,1,1,1]
0

[1,2,100,101,102]
2

[1,2,3,100,101]
2

[1,50,51,52,100]
2

[100,52,51,50,1]
2

[1,1,2,2,100]
1

[1,1000000000,1000000000]
0

[1,1,1,1000000000,1000000000,1000000000]
999999999

[4,1,3,2]
1

[9,1,9,9,1,9]
0


)");

using t2567 = SolutionTests<Solution>;

TEST_P(t2567, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimizeSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2567,
    t2567::parameters(kCases.size()),
    t2567::name);
