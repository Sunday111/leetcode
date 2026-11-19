#include "3129.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numberOfStableArrays;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
1
1
2
2

1
2
1
1

3
3
2
14

39
20
18
207227572


)");

using t3129 = SolutionTests<Solution>;

TEST_P(t3129, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numberOfStableArrays(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3129,
    t3129::parameters(kCases.size()),
    t3129::name);
