#include "2078.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,1,1,6,1,1,1] 3
[1,8,3,8,3] 4
[0,1] 1
)");

using t2078 = SolutionTests<Solution>;

TEST_P(t2078, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxDistance(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2078,
    t2078::parameters(kCases.size()),
    t2078::name);
