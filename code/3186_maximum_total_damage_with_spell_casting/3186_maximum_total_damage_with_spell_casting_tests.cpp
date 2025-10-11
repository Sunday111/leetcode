#include "3186_maximum_total_damage_with_spell_casting.hpp"
#include "gtest/gtest.h"

// TEST(t3186_maximum_total_damage_with_spell_casting, test_1)
// {
//     std::vector data{7, 1, 6, 6};
//     ASSERT_EQ(Solution{}.maximumTotalDamage(data), 13);
// }

TEST(t3186_maximum_total_damage_with_spell_casting, test_2)
{
    std::vector data{3, 4, 5, 6, 6, 7, 1, 1, 1, 1, 1,
                     9, 9, 9, 9, 9, 9, 9, 9, 9, 6};
    ASSERT_EQ(Solution{}.maximumTotalDamage(data), 104);
}
