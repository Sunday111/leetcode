#include "0472_concatenated_words.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest =
    &Solution::findAllConcatenatedWordsInADict;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
["catsdogcats","dogcatsdog","ratcatdogcat"]
)cases");

using t0472_concatenated_words = SolutionTests<Solution>;

TEST_P(t0472_concatenated_words, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args)
                { return solution.findAllConcatenatedWordsInADict(args...); },
                inputs);
            std::ranges::sort(expected);
            std::ranges::sort(actual);
            ASSERT_EQ(expected, actual);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0472_concatenated_words,
    t0472_concatenated_words::parameters(kCases.size()),
    t0472_concatenated_words::name);
