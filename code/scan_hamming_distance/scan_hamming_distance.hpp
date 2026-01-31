#include <cassert>
#include <string_view>

#include "integral_aliases.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr u8
    dist(const char* a, const char* b, u8 l) noexcept
    {
        u8 r = 0;
        for (u8 i = 0; i != l; ++i)
        {
            r += a[i] != b[i];
        }
        return r;
    }

    // n - is the maximum hamming distance between small and substring in big
    // callback is some callable that will be invoked when match is found
    template <typename Callback>
    void find_hamming_matches(
        std::string_view big,
        std::string_view small,
        u8 n,
        Callback callback) noexcept
    {
        u32 hi = static_cast<u32>(big.size());
        u8 lo = static_cast<u8>(small.size());
        const char* big_raw = big.data();
        const char* small_raw = small.data();
        for (u32 lim_i = (hi - lo) + 1, i = 0; i != lim_i; ++i)
        {
            if (dist(big_raw, small_raw, lo) <= n)
            {
                callback(big_raw);
            }
            ++big_raw;
        }
    }
};
