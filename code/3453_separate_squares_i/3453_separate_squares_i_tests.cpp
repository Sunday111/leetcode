#include "3453_separate_squares_i.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

// TEST(t3453_separate_squares_i, test_1)
// {
//     auto squares = parse2DArray("[[0,0,1],[2,2,1]]");
//     ASSERT_NEAR(Solution{}.separateSquares(squares), 1, 0.00001);
// }

TEST(t3453_separate_squares_i, test_2)
{
    auto squares = parse2DArray("[[0,0,2],[1,1,1]]");
    ASSERT_NEAR(Solution{}.separateSquares(squares), 1.16667, 0.00001);
}
