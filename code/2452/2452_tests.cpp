#include "2452.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::twoEditWords;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
["word","note","ants","wood"]
["wood","joke","moat"]
["word","note","wood"]

["yes"]
["not"]
[]
)");

using t2452 = SolutionTests<Solution>;

TEST_P(t2452, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.twoEditWords(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2452,
    t2452::parameters(kCases.size()),
    t2452::name);
