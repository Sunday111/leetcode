#include "3016.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumPushes;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abcde"                     5
"xyzxyzxyzxyz"              12
"aabbccddeeffgghhiiiiii"    24
)");

using t3016 = SolutionTests<Solution>;

TEST_P(t3016, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumPushes(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3016,
    t3016::parameters(kCases.size()),
    t3016::name);
