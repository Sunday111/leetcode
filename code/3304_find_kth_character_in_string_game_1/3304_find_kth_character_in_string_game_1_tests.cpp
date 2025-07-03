#include "3304_find_kth_character_in_string_game_1.hpp"
#include "gtest/gtest.h"

TEST(t3304_find_kth_character_in_string_game_1, test_1)
{
    Solution s{};
    for (size_t k = 1; k != 501; ++k)
    {
        std::println("{:3}: {:2}", k, s.kthCharacter(k) - 'a');
    }
}
