#include "3849.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumXor;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"101"
"011"
"110"

"0110"
"1110"
"1101"

"0101"
"1001"
"1111"


)");

using t3849 = SolutionTests<Solution>;

TEST_P(t3849, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximumXor(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3849,
    t3849::parameters(kCases.size()),
    t3849::name);
