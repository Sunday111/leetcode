#include "3741.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,1,1,3]
6

[1,1,2,3,2,1,2]
8

[1]
-1


)");

using t3741 = SolutionTests<Solution>;

TEST_P(t3741, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumDistance(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3741,
    t3741::parameters(kCases.size()),
    t3741::name);
