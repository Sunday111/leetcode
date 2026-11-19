#pragma once

#include <emmintrin.h>

#include <bit>
#include <cstdint>
#include <string>

namespace solution_sse2
{

class Solution
{
public:
    using i64 = int64_t;
    using u64 = uint64_t;

    static inline void
    interleave_bytes_sse2_u64(uint64_t a, uint64_t b, void* out) noexcept
    {
        auto ra = _mm_set_epi64x(0, std::bit_cast<i64>(a));
        auto rb = _mm_set_epi64x(0, std::bit_cast<i64>(b));
        auto p = reinterpret_cast<__m128i*>(out);  // NOLINT
        _mm_storeu_si128(p, _mm_unpacklo_epi8(ra, rb));
    }

    [[nodiscard]] static constexpr std::string mergeAlternately(
        std::string_view a,
        std::string_view b) noexcept
    {
        const u64 la = a.size(), lb = b.size(), ls = std::min(la, lb);

        std::string r;
        r.reserve(la + lb);

        if (const auto lw = ls / 8; lw)
        {
            r.resize(lw * 8);
            auto pa = reinterpret_cast<const u64*>(a.data());  // NOLINT
            auto pb = reinterpret_cast<const u64*>(b.data());  // NOLINT
            auto pr = reinterpret_cast<u64*>(r.data());        // NOLINT
            for (size_t i = 0; i != lw; ++i)
            {
                interleave_bytes_sse2_u64(pa[i], pb[i], pr + 2 * i);  // NOLINT
            }
        }

        for (size_t i = r.size() / 2; i != ls; ++i)
        {
            r.push_back(a[i]);
            r.push_back(b[i]);
        }

        r.append((la < lb ? b : a).substr(ls));

        return r;
    }
};

}  // namespace solution_sse2
