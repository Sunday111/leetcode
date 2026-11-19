#include "1768_merge_strings_alternately_simple.hpp"
#include "1768_merge_strings_alternately_sse2.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::string, std::string>,
    std::string>(R"cases(
"abc" "pqr" "apbqcr"
"ab" "pqrs" "apbqrs"
"abcd" "pq" "apbqcd"
)cases");

using t1768_merge_strings_alternately = SolutionTests<simple::Solution>;

TEST_P(t1768_merge_strings_alternately, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.mergeAlternately(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1768_merge_strings_alternately,
    t1768_merge_strings_alternately::parameters(kCases.size()),
    t1768_merge_strings_alternately::name);

using t1768_merge_strings_alternatelySse2 =
    SolutionTests<solution_sse2::Solution>;
TEST_P(t1768_merge_strings_alternatelySse2, DISABLED_Sse2)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.mergeAlternately(args...); });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1768_merge_strings_alternatelySse2,
    t1768_merge_strings_alternatelySse2::parameters(kCases.size()),
    t1768_merge_strings_alternatelySse2::name);
