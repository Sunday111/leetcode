#include "1913.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, unsigned int>(
        R"cases(
[5,6,2,7,4] 34
)cases");

using t1913 = SolutionTests<Solution>;

TEST_P(t1913, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxProductDifference(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1913,
    t1913::parameters(kCases.size()),
    t1913::name);
