#include "1329_sort_the_matrix_diagonally.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<int>>>,
    std::vector<std::vector<int>>>(R"cases(
[[3,3,1,1],[2,2,1,2],[1,1,1,2]] [[1,1,1,1],[1,2,2,2],[1,2,3,3]]

[[11,25,66,1,69,7],[23,55,17,45,15,52],[75,31,36,44,58,8],[22,27,33,25,68,4],[84,28,14,11,5,50]]
[[5,17,4,1,52,7],[11,11,25,45,8,69],[14,23,25,44,58,15],[22,27,31,36,50,66],[84,28,75,33,55,68]]
)cases");

using t1329_sort_the_matrix_diagonally = SolutionTests<Solution>;

TEST_P(t1329_sort_the_matrix_diagonally, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.diagonalSort(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1329_sort_the_matrix_diagonally,
    t1329_sort_the_matrix_diagonally::parameters(kCases.size()),
    t1329_sort_the_matrix_diagonally::name);
