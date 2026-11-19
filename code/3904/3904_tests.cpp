#include "3904.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::firstStableIndex;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[5,0,1,4]
3
3

[3,2,1]
1
-1

[0]
0
0


)");

using t3904 = SolutionTests<Solution>;

TEST_P(t3904, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.firstStableIndex(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3904,
    t3904::parameters(kCases.size()),
    t3904::name);
