#include "3607.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<
        unsigned int,
        std::vector<std::vector<int>>,
        std::vector<std::vector<int>>>,
    std::vector<int>>(R"cases(
5 [[1,2],[2,3],[3,4],[4,5]] [[1,3],[2,1],[1,1],[2,2],[1,2]] [3,2,3]
)cases");

using t3607 = SolutionTests<Solution>;

TEST_P(t3607, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.processQueries(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3607,
    t3607::parameters(kCases.size()),
    t3607::name);
