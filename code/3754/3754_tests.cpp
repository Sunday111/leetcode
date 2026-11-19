#include "3754.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::sumAndMultiply;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
10203004
12340

1000
1


)");

using t3754 = SolutionTests<Solution>;

TEST_P(t3754, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.sumAndMultiply(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3754,
    t3754::parameters(kCases.size()),
    t3754::name);
