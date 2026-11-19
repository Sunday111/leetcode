#include "3720.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::lexGreaterPermutation;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abc"
"bba"
"bca"

"leet"
"code"
"eelt"

"baba"
"bbaa"
""


)");

using t3720 = SolutionTests<Solution>;

TEST_P(t3720, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.lexGreaterPermutation(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3720,
    t3720::parameters(kCases.size()),
    t3720::name);
