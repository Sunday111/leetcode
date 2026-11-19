#include <algorithm>

#include "0140_word_break_2.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::string_view, std::vector<std::string>>,
    std::vector<std::string>>(R"cases(
"catsanddog" ["and","cat","cats","dog","sand"] ["cat sand dog","cats and dog"]

"pineapplepenapple"
["apple","applepen","pen","pine","pineapple"]
["pine apple pen apple","pine applepen apple","pineapple pen apple"]
)cases");

using t0140_word_break_2 = SolutionTests<Solution>;

TEST_P(t0140_word_break_2, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args) { return solution.wordBreak(args...); },
                inputs);
            std::ranges::sort(expected);
            std::ranges::sort(actual);
            ASSERT_EQ(expected, actual);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0140_word_break_2,
    t0140_word_break_2::parameters(kCases.size()),
    t0140_word_break_2::name);
