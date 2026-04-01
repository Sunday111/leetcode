#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;

    struct Entry
    {
        u32 pos;
        u32 idx;

        [[nodiscard, gnu::always_inline]] bool is_left() const noexcept
        {
            return pos >> 31;
        }
    };

    inline static Entry radix_buffer[100000];
    inline static u32 count[1 << 16];

    template <u32 bits_per_pass, u32 num_passes, u32 Entry::* Member>
    [[gnu::hot]] static void radix_sort(Entry* a, u32 n) noexcept
    {
        constexpr u32 radix = 1u << bits_per_pass;
        constexpr u32 mask = radix - 1u;

        if (n <= 1u) return;

        for (u32 pass = 0u; pass != num_passes; ++pass)
        {
            const u32 shift = pass * bits_per_pass;

            std::fill_n(count, radix, 0u);

            for (u32 i = 0u; i != n; ++i)
            {
                const u32 key = ((a[i].*Member) >> shift) & mask;
                ++count[key];
            }

            std::exclusive_scan(count, count + radix, count, 0u, std::plus{});

            for (u32 i = 0u; i != n; ++i)
            {
                u32 key = ((a[i].*Member) >> shift) & mask;
                radix_buffer[count[key]++] = a[i];
            }

            std::copy_n(radix_buffer, n, a);
        }
    }

    std::vector<int> survivedRobotsHealths(
        std::vector<int>& pos_,
        std::vector<int>& hp_,
        std::string& dir) noexcept
    {
        const u32 n = static_cast<u32>(pos_.size());
        auto& pos = reinterpret_cast<std::vector<u32>&>(pos_);
        auto& hp = reinterpret_cast<std::vector<u32>&>(hp_);

        static Entry e[100000];
        for (u32 i = 0; i != n; ++i)
        {
            e[i] = {
                .pos = (pos[i]) | (u32{dir[i] == 'L'} << 31),
                .idx = i,
            };
        }

        radix_sort<10, 3, &Entry::pos>(e, n);

        for (u32 i = 1, k = !e[0].is_left(); i != n; ++i)
        {
            auto& a = e[i];
            auto& b = e[std::min(k - 1, k)];
            bool t1 = a.is_left();
            bool t2 = t1 && k;
            u32& ha = hp[a.idx];
            u32& hb = hp[b.idx];
            bool ba = ha > hb;
            bool bb = hb > ha;
            (ha -= t2) &= -u32{!t2 || ba};
            (hb -= t2) &= -u32{!t2 || bb};
            i -= t2 && ba;
            k -= t2 && !bb;
            e[k] = e[i];
            k += !t1;
        }

        u32 alive = 0;
        for (auto x : hp)
        {
            pos[alive] = x;
            alive += !!x;
        }

        pos.resize(alive);

        return pos_;
    }
};

#include "sync_stdio.hpp"
