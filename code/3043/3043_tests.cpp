#include "3043.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::longestCommonPrefix;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,10,100]
[1000]
3

[1,2,3]
[4,4,4]
0
)");

using t3043 = SolutionTests<Solution>;

TEST_P(t3043, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.longestCommonPrefix(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3043,
    t3043::parameters(kCases.size()),
    t3043::name);
