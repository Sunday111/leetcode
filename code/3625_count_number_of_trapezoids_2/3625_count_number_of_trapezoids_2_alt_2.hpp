#include <numeric>
#include <unordered_map>
#include <vector>

#include "bump_hash_map.hpp"
#include "force_inline.hpp"
#include "integral_aliases.hpp"
#include "negate_if.hpp"

using SolutionStorage = GlobalBufferStorage<1 << 25>;
class Solution
{
public:
    inline static constexpr int kBias = 1 << 11;

    FORCE_INLINE static u32 pack(int a, int b) noexcept
    {
        return std::bit_cast<u32>(i32{a + kBias} << 16) |
               std::bit_cast<u32>(b + kBias);
    }

    FORCE_INLINE static u64 pack(int a, int b, int c) noexcept
    {
        return std::bit_cast<u64>(i64{a + kBias} << 50) |
               std::bit_cast<u64>(i64{b + kBias} << 30) |
               std::bit_cast<u64>(i64{c + kBias * kBias});
    }

    FORCE_INLINE static u64 pack(int a, int b, int c, int d) noexcept
    {
        return std::bit_cast<u64>(i64{a + kBias} << 48) |
               std::bit_cast<u64>(i64{b + kBias} << 32) |
               std::bit_cast<u64>(i64{c + kBias} << 16) |
               std::bit_cast<u64>(i64{d + kBias});
    }

    static u32 countTrapezoids(std::vector<std::vector<int>>& points)
    {
        auto arena = SolutionStorage::Instance().StartArena();
        ObjectWithoutDtor<BumpHashMap<u32, u32, SolutionStorage>> slope;
        ObjectWithoutDtor<BumpHashMap<u64, u32, SolutionStorage>> coeff,
            midPointWslope, midPoint;

        const u16 n = points.size() & 0xFFFF;
        const u32 nn = u32{n} * (u32{n} - 1);

        coeff->reserve(nn);
        slope->reserve(nn);
        midPointWslope->reserve(nn);
        midPoint->reserve(nn);

        u32 cnt = 0;
        for (u16 i = 0; i != n - 1; ++i)
        {
            const int x0 = points[i][0], y0 = points[i][1];
            for (u16 j = i + 1; j != n; ++j)
            {
                const int x1 = points[j][0], y1 = points[j][1];
                int a = y1 - y0, b = x0 - x1, c = y0 * x1 - y1 * x0;
                bool c1 = !a && b < 0;
                bool c2 = a < 0;
                bool c3 = !c1 && c2;
                bool c4 = c1 || c2;
                a = negate_if(c3, a);
                b = negate_if(c4, b);
                c = negate_if(c4, c);
                int gm = std::gcd(a, b), gc = std::gcd(gm, c);
                auto ab = pack(a / gm, b / gm);
                auto abc = pack(a / gc, b / gc, c / gc);
                auto mp = pack(x0 + x1, y0 + y1);
                auto mab = pack(x0 + x1, y0 + y1, a / gm, b / gm);
                cnt += (slope.get()[ab]++) - (coeff.get()[abc]++) -
                       (midPoint.get()[mp]++) + (midPointWslope.get()[mab]++);
            }
        }
        return cnt;
    }
};
