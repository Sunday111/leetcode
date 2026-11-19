#include "3551.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minSwaps;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,1,2]
2

[18,43,34,16]
2

[22,14,33,7]
0

[37,100]
1

)");

using t3551 = SolutionTests<Solution>;

TEST_P(t3551, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minSwaps(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3551,
    t3551::parameters(kCases.size()),
    t3551::name);
