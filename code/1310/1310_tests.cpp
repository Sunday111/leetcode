#include "1310.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::xorQueries;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,4,8]
[[0,1],[1,2],[0,3],[3,3]]
[2,7,14,8]

[4,8,2,10]
[[2,3],[1,3],[0,0],[0,3]]
[8,0,4,4]
)");

using t1310 = SolutionTests<Solution>;

TEST_P(t1310, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.xorQueries(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1310,
    t1310::parameters(kCases.size()),
    t1310::name);
