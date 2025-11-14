#include <cstdint>
#include <numeric>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

#define FORCE_INLINE inline __attribute__((always_inline))

template <typename To>
[[nodiscard]] FORCE_INLINE static constexpr To to(auto v) noexcept
{
    return static_cast<To>(v);
}

class Solution
{
public:
    static std::vector<std::vector<int>> rangeAddQueries(
        u32 n,
        std::vector<std::vector<int>>& queries)
    {
        std::vector<std::vector<int>> t(n + 1);
        for (auto& r : t)
        {
            r.resize(n + 1, 0);
        }

        for (auto& q : queries)
        {
            u32 y0 = to<u32>(q[0]);
            u32 x0 = to<u32>(q[1]);
            u32 y1 = to<u32>(q[2] + 1);
            u32 x1 = to<u32>(q[3] + 1);
            ++t[y0][x0];
            --t[y0][x1];
            --t[y1][x0];
            ++t[y1][x1];
        }

        for (u32 y = 0; y != n; ++y)
        {
            auto& r = t[y];
            r.resize(n);
            std::inclusive_scan(r.begin(), r.end(), r.begin());
        }

        for (u32 y = 1; y != n; ++y)
        {
            auto &r = t[y], &pr = t[y - 1];
            for (u32 x = 0; x != n; ++x) r[x] += pr[x];
        }

        t.resize(n);
        return t;
    }
};
