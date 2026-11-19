#include "1291.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::sequentialDigits;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
100
300
[123, 234]

1000
13000
[1234,2345,3456,4567,5678,6789,12345]
)");

using t1291 = SolutionTests<Solution>;

TEST_P(t1291, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.sequentialDigits(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1291,
    t1291::parameters(kCases.size()),
    t1291::name);
