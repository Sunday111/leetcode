#include <algorithm>
#include <bit>
#include <bitset>
#include <cstdint>
#include <span>
#include <vector>

using u32 = uint32_t;

struct GridAdapter
{
    explicit GridAdapter(u32* in, u32 n) noexcept
        : data_{in},
          stride_bits_{static_cast<u32>(std::bit_width(n))}
    {
    }

    template <typename Self>
    decltype(auto) operator[](this Self&& self, u32 i, u32 j)
    {
        return std::forward<Self>(self).data_[(i << self.stride_bits_) + j];
    }

    auto get_row(this auto&& self, u32 i)
    {
        return std::span{
            self.data_ + (i << self.stride_bits_),
            1u << self.stride_bits_};
    }

    u32* data_;
    u32 stride_bits_;
};

class Solution
{
public:
    inline static u32 buf[100 * 128];
    inline static constexpr u32 inf = (~u32{}) / 2;
    u32 findTheCity(
        const u32 n,
        std::vector<std::vector<int>>& edges,
        u32 distanceThreshold) const noexcept
    {
        GridAdapter dist(buf, n);
        for (u32 i = 0; i != n; ++i)
        {
            std::ranges::fill(dist.get_row(i), inf);
            dist[i, i] = 0;
        }

        // Floyd-Warshall Algorithm
        std::bitset<128> connected;
        for (auto& edge : edges)
        {
            u32 i = edge[0] & 127, j = edge[1] & 127;
            dist[i, j] = dist[j, i] = edge[2] & 0xFFFF;
            connected[i] = true;
            connected[j] = true;
        }

        if (connected.count() != n)
        {
            u32 ans = n;
            while (connected[--ans]);
            return ans;
        }

        for (u32 k = 0; k != n; ++k)
        {
            for (u32 i = 0; i != n; ++i)
            {
                if (dist[i, k] == inf) continue;
                for (u32 j = 0; j != n; ++j)
                {
                    dist[i, j] = std::min(dist[i, j], dist[i, k] + dist[k, j]);
                }
            }
        }

        u32 ans = 0, ans_count = inf;
        for (u32 i = 0; i != n; ++i)
        {
            u32 cnt = 0;
            for (u32 j = 0; j != n; ++j)
            {
                cnt += dist[i, j] <= distanceThreshold;
            }
            ans_count = std::min(ans_count, cnt);
            if (cnt == ans_count)
            {
                ans = i;
            }
        }

        return ans;
    }
};
