#include "2056_number_of_valid_move_combinations_on_chessboard.hpp"
#include "gtest/gtest.h"

TEST(t2056_number_of_valid_move_combinations_on_chessboard, test_1)
{
    std::vector<std::string> pieces{"rook"};
    std::vector<std::vector<int>> positions = {{1, 1}};
    ASSERT_EQ(Solution{}.countCombinations(pieces, positions), 15);
}

TEST(t2056_number_of_valid_move_combinations_on_chessboard, test_2)
{
    std::vector<std::string> pieces{"queen"};
    std::vector<std::vector<int>> positions = {{1, 1}};
    ASSERT_EQ(Solution{}.countCombinations(pieces, positions), 22);
}

TEST(t2056_number_of_valid_move_combinations_on_chessboard, test_3)
{
    std::vector<std::string> pieces{"bishop"};
    std::vector<std::vector<int>> positions = {{4, 3}};
    ASSERT_EQ(Solution{}.countCombinations(pieces, positions), 12);
}

TEST(t2056_number_of_valid_move_combinations_on_chessboard, test_4)
{
    std::vector<std::string> pieces{"rook", "rook"};
    std::vector<std::vector<int>> positions = {{1, 1}, {8, 8}};
    ASSERT_EQ(Solution{}.countCombinations(pieces, positions), 223);
}

TEST(t2056_number_of_valid_move_combinations_on_chessboard, test_5)
{
    std::vector<std::string> pieces{"rook", "rook"};
    std::vector<std::vector<int>> positions = {{1, 1}, {1, 7}};
    ASSERT_EQ(Solution{}.countCombinations(pieces, positions), 189);
}
