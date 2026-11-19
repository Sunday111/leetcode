#include "0242_valid_anagram.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isAnagram;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"anagram" "nagaram" true

"rat" "car" false
)cases");

using t0242_valid_anagram = SolutionTests<Solution>;

TEST_P(t0242_valid_anagram, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.isAnagram(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0242_valid_anagram,
    t0242_valid_anagram::parameters(kCases.size()),
    t0242_valid_anagram::name);
