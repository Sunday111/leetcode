#include "1356_sort_integers_by_the_number_of_1_bits.hpp"
#include "gtest/gtest.h"

TEST(t1356_sort_integers_by_the_number_of_1_bits, test_1)
{
    std::vector original{0, 1, 2, 3, 4, 5, 6, 7, 8};
    std::vector expected{0, 1, 2, 4, 8, 3, 5, 6, 7};
    auto actual = Solution{}.sortByBits(original);
    ASSERT_EQ(expected, actual);
}

TEST(t1356_sort_integers_by_the_number_of_1_bits, test_2)
{
    std::vector original{1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1};
    std::vector expected{1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    auto actual = Solution{}.sortByBits(original);
    ASSERT_EQ(expected, actual);
}
