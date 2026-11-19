#include "1331.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::arrayRankTransform;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[40,10,20,30] [4,1,2,3]
[100,100,100] [1,1,1]
[37,12,28,9,100,56,80,5,12] [5,3,4,2,8,6,7,1,3]
)");

using t1331 = SolutionTests<Solution>;

TEST_P(t1331, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.arrayRankTransform(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1331,
    t1331::parameters(kCases.size()),
    t1331::name);
