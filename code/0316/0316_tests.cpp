#include "0316.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::removeDuplicateLetters;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"bcabc"    "abc"
"cbacdcbc" "acdb"
)");

using t0316 = SolutionTests<Solution>;

TEST_P(t0316, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.removeDuplicateLetters(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0316,
    t0316::parameters(kCases.size()),
    t0316::name);
