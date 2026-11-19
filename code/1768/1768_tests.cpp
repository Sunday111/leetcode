#include "1768_simple.hpp"
#include "1768_sse2.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::string, std::string>,
    std::string>(R"cases(
"abc" "pqr" "apbqcr"
"ab" "pqrs" "apbqrs"
"abcd" "pq" "apbqcd"
)cases");

using t1768 = SolutionTests<simple::Solution>;

TEST_P(t1768, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.mergeAlternately(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1768,
    t1768::parameters(kCases.size()),
    t1768::name);

using t1768Sse2 = SolutionTests<solution_sse2::Solution>;
TEST_P(t1768Sse2, DISABLED_Sse2)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.mergeAlternately(args...); });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1768Sse2,
    t1768Sse2::parameters(kCases.size()),
    t1768Sse2::name);
