#include "2126.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::asteroidsDestroyed;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
10
[3,9,19,5,21]
true
5
[4,9,23,4]
false
)");

using t2126 = SolutionTests<Solution>;

TEST_P(t2126, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.asteroidsDestroyed(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2126,
    t2126::parameters(kCases.size()),
    t2126::name);
