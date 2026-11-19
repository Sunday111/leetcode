#include "1784.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::checkOnesSegment;

inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"1001"
false

"110"
true

)");

using t1784 = SolutionTests<Solution>;

TEST_P(t1784, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.checkOnesSegment(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1784,
    t1784::parameters(kCases.size()),
    t1784::name);
