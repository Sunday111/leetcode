#include "3003_maximize_the_number_of_partitions_after_operations.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxPartitionsAfterOperations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"accca" 2 3

"aabaab" 3 1

"xxyz" 1 4

"bbbbcbcbbc" 2 3
)cases");

using t3003_maximize_the_number_of_partitions_after_operations =
    SolutionTests<Solution>;

TEST_P(t3003_maximize_the_number_of_partitions_after_operations, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxPartitionsAfterOperations(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3003_maximize_the_number_of_partitions_after_operations,
    t3003_maximize_the_number_of_partitions_after_operations::parameters(
        kCases.size()),
    t3003_maximize_the_number_of_partitions_after_operations::name);
