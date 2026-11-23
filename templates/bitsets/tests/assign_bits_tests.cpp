#include <gtest/gtest.h>

#include <cstdint>

#include "bitsets/assign_bits.hpp"

TEST(Bitsets, AssignBits)
{
    static_assert(assign_bits<true>(0xA0u, 0x0Fu) == 0xAFu);
    static_assert(assign_bits<false>(0xAFu, 0x0Fu) == 0xA0u);
    for (unsigned word = 0; word != 256; ++word)
    {
        for (unsigned mask = 0; mask != 256; ++mask)
        {
            const auto w = static_cast<std::uint8_t>(word);
            const auto m = static_cast<std::uint8_t>(mask);
            EXPECT_EQ(assign_bits<true>(w, m), word | mask);
            EXPECT_EQ(assign_bits<false>(w, m), word & ~mask);
        }
    }
}
