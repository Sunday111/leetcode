#include "1823_find_the_winner_of_the_circular_game.hpp"
#include "gtest/gtest.h"

TEST(t1823_find_the_winner_of_the_circular_game, test_1)
{
    using u16 = uint16_t;
    auto simple = [](u16 n, u16 k)
    {
        std::vector<u16> a;
        a.reserve(n);
        for (u16 i = 0; i != n;) a.push_back(++i);

        --k;
        for (u16 p = 0; n != 1; --n)
        {
            p += k;
            p %= n;
            a.erase(std::next(a.begin(), p));
        }

        return a.front();
    };

    for (uint16_t n = 1; n != 100; ++n)
    {
        for (uint16_t k = 1; k <= n; ++k)
        {
            ASSERT_EQ(simple(n, k), Solution::findTheWinner(n, k));
        }
    }
}
