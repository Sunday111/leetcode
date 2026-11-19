#include "3756.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::sumAndMultiply;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"10203004"
[[0,7],[1,3],[4,6]]
[12340, 4, 9]

"1000"
[[0,3],[1,1]]
[1, 0]

"9876543210"
[[0,9]]
[444444137]


)");

using t3756 = SolutionTests<Solution>;

TEST_P(t3756, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.sumAndMultiply(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3756,
    t3756::parameters(kCases.size()),
    t3756::name);
