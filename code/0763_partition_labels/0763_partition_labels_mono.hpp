#include <concepts>
#include <cstdint>
#include <string>
#include <vector>





#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

template <std::unsigned_integral T>
[[nodiscard]] FORCE_INLINE static constexpr T
clear_bit(T x, u8 i, bool condition = true) noexcept
{
    return x & ~(T{condition} << i);
}

class Solution
{
public:
    constexpr auto partitionLabels(const std::string& s) noexcept
    {
        u32 lb = 0, rb = 0;
        u16 n = 0, freq[26]{};
        std::vector<int> r;

        for (char c : s)
        {
            u8 i = (c - 'a') & 31;
            rb |= (1u << i);
            ++freq[i];
        }

        for (char c : s)
        {
            u8 i = (c - 'a') & 31;

            rb = clear_bit(rb, i, !--freq[i]);
            lb |= (1u << i);
            ++n;

            if (lb & rb) continue;
            r.emplace_back(n);
            lb = 0;
            n = 0;
        }

        return r;
    }
};
