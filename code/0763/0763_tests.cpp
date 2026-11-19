#include "0763_test_cases.hpp"
#include "solution_tests.hpp"

using t0763_partition_labels = SolutionTests<Solution>;

TEST_P(t0763_partition_labels, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.partitionLabels(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0763_partition_labels,
    t0763_partition_labels::parameters(kCases.size()),
    t0763_partition_labels::name);
