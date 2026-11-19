#include "0242.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isAnagram;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"anagram" "nagaram" true

"rat" "car" false
)cases");

using t0242 = SolutionTests<Solution>;

TEST_P(t0242, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.isAnagram(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0242,
    t0242::parameters(kCases.size()),
    t0242::name);
