#include "0950_reveal_cards_in_increasing_order.hpp"
#include "gtest/gtest.h"

TEST(t0950_reveal_cards_in_increasing_order, test_1)
{
    std::vector deck{17, 13, 11, 2, 3, 5, 7};
    std::vector expected{2, 13, 3, 11, 5, 17, 7};
    auto actual = Solution{}.deckRevealedIncreasing(deck);
    ASSERT_EQ(expected, actual);
}
