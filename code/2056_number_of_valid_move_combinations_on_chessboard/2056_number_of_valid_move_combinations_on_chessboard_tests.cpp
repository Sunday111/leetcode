#include "2056_number_of_valid_move_combinations_on_chessboard.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countCombinations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["rook"] [[1,1]] 15

["queen"] [[1,1]] 22

["bishop"] [[4,3]] 12

["rook","rook"] [[1,1],[8,8]] 223

["rook","rook"] [[1,1],[1,7]] 189
)cases");

using t2056_number_of_valid_move_combinations_on_chessboard =
    SolutionTests<Solution>;

TEST_P(t2056_number_of_valid_move_combinations_on_chessboard, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countCombinations(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2056_number_of_valid_move_combinations_on_chessboard,
    t2056_number_of_valid_move_combinations_on_chessboard::parameters(
        kCases.size()),
    t2056_number_of_valid_move_combinations_on_chessboard::name);
