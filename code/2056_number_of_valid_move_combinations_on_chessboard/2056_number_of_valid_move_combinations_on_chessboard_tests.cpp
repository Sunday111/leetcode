#include "2056_number_of_valid_move_combinations_on_chessboard.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countCombinations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["rook"] [[1,1]] 15

["queen"] [[1,1]] 22

["bishop"] [[4,3]] 12

["rook","rook"] [[1,1],[8,8]] 223

["rook","rook"] [[1,1],[1,7]] 189
)cases");

class t2056_number_of_valid_move_combinations_on_chessboard
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2056_number_of_valid_move_combinations_on_chessboard, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.countCombinations(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2056_number_of_valid_move_combinations_on_chessboard,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
