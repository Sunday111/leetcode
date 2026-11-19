#include "1248.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numberOfSubarrays;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,1,2,1,1]
3
2
[2,4,6]
1
0
[2,2,2,1,2,2,1,2,2,2]
2
16
)");

using t1248 = SolutionTests<Solution>;

TEST_P(t1248, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numberOfSubarrays(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1248,
    t1248::parameters(kCases.size()),
    t1248::name);
