#include "3823_reverse_letters_then_special_characters_in_a_string.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::reverseByType;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
")ebc#da@f(" "(fad@cb#e)"

"!@#$%^&*()" ")(*&^%$#@!"
)cases");

using t3823_reverse_letters_then_special_characters_in_a_string =
    SolutionTests<Solution>;

TEST_P(t3823_reverse_letters_then_special_characters_in_a_string, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.reverseByType(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3823_reverse_letters_then_special_characters_in_a_string,
    t3823_reverse_letters_then_special_characters_in_a_string::parameters(
        kCases.size()),
    t3823_reverse_letters_then_special_characters_in_a_string::name);
