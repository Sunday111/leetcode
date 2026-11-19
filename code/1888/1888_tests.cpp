#include "1888.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minFlips;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"111000"
2

"010"
0

"1110"
1

)");

using t1888 = SolutionTests<Solution>;

TEST_P(t1888, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minFlips(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1888,
    t1888::parameters(kCases.size()),
    t1888::name);
