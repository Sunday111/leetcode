#include "0368_lexicographical_numbers.hpp"
#include "gtest/gtest.h"

TEST(t0368_lexicographical_numbers, test_1)
{
    std::vector expected{1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_EQ(Solution{}.lexicalOrder(13), expected);
}
