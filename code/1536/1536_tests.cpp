#include "1536.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minSwaps;

inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,0,1],[1,1,0],[1,0,0]]
3

[[0,1,1,0],[0,1,1,0],[0,1,1,0],[0,1,1,0]]
-1

[[1,0,0],[1,1,0],[1,1,1]]
0

)");

using t1536 = SolutionTests<Solution>;

TEST_P(t1536, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minSwaps(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1536,
    t1536::parameters(kCases.size()),
    t1536::name);
