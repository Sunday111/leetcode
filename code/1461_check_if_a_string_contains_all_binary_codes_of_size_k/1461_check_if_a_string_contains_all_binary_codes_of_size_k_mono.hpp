#include <cstdint>
#include <string_view>



#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    // s.size: [1; 5 * 10^5]
    [[nodiscard]] static bool hasAllCodes(
        const std::string_view s,
        const u32 k) noexcept
    {
        const u32 t = 1u << k;
        const u32 m = t - 1;
        const u32 n = static_cast<u32>(s.size());

        // Before doing any heavy stuff
        // check if it is possible to represent
        // t values having a string of size n
        if (n + 1 < t + k) return false;

        // Maximum length of s is 500k so
        // the biggest k worth checking is 18
        // (2^19 > 500k)
        static u64 bitset_words[1 << 12];

        // clear the static bitset before using it
        std::fill_n(bitset_words, (t >> 6) + 1, 0);

        u32 v = 0;
        auto visit = [&](u32 i) INLINE_LAMBDA
        {
            u64& w = bitset_words[i >> 6];
            u64 m = (u64{1} << (i & 63));
            v += !(w & m);
            w |= m;
        };

        u32 x = 0;
        auto add_bit = [&](char c) INLINE_LAMBDA
        {
            x = ((x << 1) | (1 & c)) & m;
        };

        for (u32 i = 0; i != k; ++i)
        {
            add_bit(s[i]);
        }

        visit(x);
        for (u32 i = k; v < t && n + v >= t + i; ++i)
        {
            add_bit(s[i]);
            visit(x);
        }

        return v == t;
    }
};
