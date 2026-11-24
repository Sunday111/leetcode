#include <gtest/gtest.h>

#include "bitsets/bswap.hpp"

TEST(Bitsets, Bswap)
{
    constexpr u64 high = 0x0123456789ABCDEF;
    constexpr u64 low = 0x1032547698BADCFE;
    constexpr u128 wide = (u128{high} << 64) | low;
    constexpr u128 reversed =
        (u128{0xFEDCBA9876543210} << 64) | 0xEFCDAB8967452301;
    static_assert(bswap(u8{0xA5}) == 0xA5);
    static_assert(bswap(u16{0x0180}) == 0x8001);
    static_assert(bswap(u32{0x01020304}) == 0x04030201);
    static_assert(bswap(high) == 0xEFCDAB8967452301);
    static_assert(bswap(wide) == reversed);
    auto check = []<typename Word>(Word value)
    {
        static_assert(std::same_as<decltype(bswap(value)), Word>);
        EXPECT_EQ(bswap(bswap(value)), value);
    };
    check(u8{0xA5});
    check(u16{0x0180});
    check(u32{0x01020304});
    check(high);
    check(wide);
}
