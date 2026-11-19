#include "3300.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minElement;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[10,12,13,14]
1

[1,2,3,4]
1

[999,19,199]
10


)");

using t3300 = SolutionTests<Solution>;

TEST_P(t3300, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minElement(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3300,
    t3300::parameters(kCases.size()),
    t3300::name);
