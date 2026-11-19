#include "3775_reverse_words_with_same_vowel_count.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::reverseWords;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"cat and mice" "cat dna mice"
)cases");

using t3775_reverse_words_with_same_vowel_count = SolutionTests<Solution>;

TEST_P(t3775_reverse_words_with_same_vowel_count, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.reverseWords(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3775_reverse_words_with_same_vowel_count,
    t3775_reverse_words_with_same_vowel_count::parameters(kCases.size()),
    t3775_reverse_words_with_same_vowel_count::name);
