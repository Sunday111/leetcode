#include <cstdint>
#include <cstdlib>
#include <numeric>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

class Solution
{
public:
    [[nodiscard]] static FORCE_INLINE int gcd_abs(int a, int b) noexcept
    {
        if (a == 0) return std::abs(b);
        if (b == 0) return std::abs(a);
        return std::gcd(abs(a), abs(b));
    }

    [[nodiscard]] FORCE_INLINE static constexpr auto comb_2(
        std::integral auto n) noexcept
    {
        return (n * (n - 1)) / 2;
    }

    i64 countTrapezoids(std::vector<std::vector<int>>& pts)
    {
        const int n = pts.size();
        const int m = n * (n - 1) / 2;
        if (m <= 0) return 0;

        static std::vector<u32> sk;
        sk.clear();
        sk.reserve(m);

        static std::vector<u32> sumk;
        sumk.clear();
        sumk.reserve(m);

        static std::vector<u32> b;
        b.clear();
        b.reserve(m);

        constexpr int OFF = 2048;
        constexpr int MIDOFF = 2000;

        for (int i = 0; i < n; ++i)
        {
            const auto& A = pts[i];
            for (int j = i + 1; j < n; ++j)
            {
                const auto& B = pts[j];
                int dx = B[0] - A[0];
                int dy = B[1] - A[1];

                int nx, ny;
                if (dx == 0 && dy == 0)
                {
                    nx = 0;
                    ny = 0;
                }
                else if (dx == 0)
                {
                    nx = -1;
                    ny = 0;
                }
                else if (dy == 0)
                {
                    nx = 0;
                    ny = 1;
                }
                else
                {
                    int g = gcd_abs(dx, dy);
                    int tx = dx / g;
                    int ty = dy / g;
                    if (tx < 0)
                    {
                        nx = ty;
                        ny = -tx;
                    }
                    else
                    {
                        nx = -ty;
                        ny = tx;
                    }
                }
                u32 ski = ((u32)((nx + OFF) & 0xFFFF) << 16) |
                          (u32)((ny + OFF) & 0xFFFF);
                sk.push_back(ski);

                int mx = A[0] + B[0] + MIDOFF;
                int my = A[1] + B[1] + MIDOFF;
                u32 sumi = ((u32)(mx & 0xFFFF) << 16) | (u32)(my & 0xFFFF);
                sumk.push_back(sumi);

                int bi = A[0] * nx + A[1] * ny;
                b.push_back((u32)bi);
            }
        }

        std::vector<int> idx(m), tmp_idx(m);
        for (int i = 0; i < m; ++i) idx[i] = i;

        static uint32_t cnt[1 << 16];

        auto radix_sort_idx_by_64 =
            [&](const std::vector<u32>& hi, const std::vector<u32>& lo)
        {
            int sz = m;
            memset(cnt, 0, sizeof(cnt));
            for (int i = 0; i < sz; ++i) ++cnt[(lo[idx[i]]) & 0xFFFF];
            uint32_t sum = 0;
            for (int t = 0; t < 65536; ++t)
            {
                uint32_t c = cnt[t];
                cnt[t] = sum;
                sum += c;
            }
            for (int i = 0; i < sz; ++i)
                tmp_idx[cnt[(lo[idx[i]]) & 0xFFFF]++] = idx[i];
            idx.swap(tmp_idx);

            memset(cnt, 0, sizeof(cnt));
            for (int i = 0; i < sz; ++i) ++cnt[(lo[idx[i]] >> 16) & 0xFFFF];
            sum = 0;
            for (int t = 0; t < 65536; ++t)
            {
                uint32_t c = cnt[t];
                cnt[t] = sum;
                sum += c;
            }
            for (int i = 0; i < sz; ++i)
                tmp_idx[cnt[(lo[idx[i]] >> 16) & 0xFFFF]++] = idx[i];
            idx.swap(tmp_idx);

            memset(cnt, 0, sizeof(cnt));
            for (int i = 0; i < sz; ++i) ++cnt[(hi[idx[i]]) & 0xFFFF];
            sum = 0;
            for (int t = 0; t < 65536; ++t)
            {
                uint32_t c = cnt[t];
                cnt[t] = sum;
                sum += c;
            }
            for (int i = 0; i < sz; ++i)
                tmp_idx[cnt[(hi[idx[i]]) & 0xFFFF]++] = idx[i];
            idx.swap(tmp_idx);

            memset(cnt, 0, sizeof(cnt));
            for (int i = 0; i < sz; ++i) ++cnt[(hi[idx[i]] >> 16) & 0xFFFF];
            sum = 0;
            for (int t = 0; t < 65536; ++t)
            {
                uint32_t c = cnt[t];
                cnt[t] = sum;
                sum += c;
            }
            for (int i = 0; i < sz; ++i)
                tmp_idx[cnt[(hi[idx[i]] >> 16) & 0xFFFF]++] = idx[i];
            idx.swap(tmp_idx);
        };

        auto compute_pair_sum = [&](const vector<u32>& hi,
                                    const vector<u32>& lo) -> i64
        {
            i64 res = 0;
            int i = 0;
            while (i < m)
            {
                u32 h = hi[idx[i]];
                int j = i;
                while (j < m && hi[idx[j]] == h) ++j;
                int cur = i;
                while (cur < j)
                {
                    int k = cur + 1;
                    while (k < j && lo[idx[k]] == lo[idx[cur]]) ++k;
                    i64 t = k - cur;
                    res += t * (cur - i);
                    cur = k;
                }
                i = j;
            }
            return res;
        };

        radix_sort_idx_by_64(sk, b);
        i64 S = compute_pair_sum(sk, b);

        for (int i = 0; i < m; ++i) idx[i] = i;
        radix_sort_idx_by_64(sumk, sk);
        i64 P = compute_pair_sum(sumk, sk);

        i64 ans = S - P;
        if (ans < 0) ans = 0;
        return ans;
    }
};
