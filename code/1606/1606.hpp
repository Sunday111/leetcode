#include <algorithm>
#include <limits>
#include <utility>
#include <vector>

#include "integral_aliases.hpp"
#include "pyramid_bitset/pbs_add.hpp"
#include "pyramid_bitset/pbs_add_if.hpp"
#include "pyramid_bitset/pbs_initialize.hpp"
#include "pyramid_bitset/pbs_make.hpp"
#include "pyramid_bitset/pbs_next_inclusive.hpp"
#include "pyramid_bitset/pbs_remove.hpp"
#include "sync_stdio.hpp"

class Solution
{
    static constexpr u32 kCapacity = 100'000;

    inline static u64 free_words[PyramidBitset<kCapacity>::kTotalWords];

    class BusyHeap
    {
        struct Entry
        {
            u32 time, server;
        };
        alignas(64) inline static Entry data[kCapacity + 1];

    public:
        u32 size = 0;

        [[nodiscard, gnu::always_inline]] u32 time() const noexcept
        {
            return data[1].time;
        }

        [[gnu::always_inline]] void push(u32 time, u32 server) noexcept
        {
            const Entry value{time, server};
            u32 i = ++size;
            while (value.time < data[i >> 1].time)
            {
                data[i] = data[i >> 1];
                i >>= 1;
            }
            data[i] = value;
        }

        [[nodiscard, gnu::always_inline]] u32 pop() noexcept
        {
            const u32 server = data[1].server;
            const Entry value = data[size--];
            data[size + 1].time = ~u32{};
            u32 i = 1;
            for (u32 child = 2; child <= size; child = i << 1)
            {
                child += data[child + 1].time < data[child].time;
                if (value.time <= data[child].time) break;
                data[i] = data[child];
                i = child;
            }
            data[i] = value;
            return server;
        }
    };

    alignas(64) inline static u32 cnt[kCapacity];

public:
    template <u32 max_k>
    [[gnu::no_sanitize_address,
      gnu::flatten,
      gnu::target("arch=skylake")]] static void
    impl(
        u32 k,
        std::vector<u32>& arrivals,
        const std::vector<u32>& loads) noexcept
    {
        const u32 num_requests = arrivals.size() & ~u32{};
        {
            u32* arrival_data = arrivals.data();
            if (k == 1)
            {
                arrival_data[0] = 0;
                arrivals.resize(1);
                return;
            }
            if (num_requests <= k)
            {
                for (u32 i = 0; i != num_requests; ++i) arrival_data[i] = i;
                return;
            }
        }

        const u32* const arrival_data = arrivals.data();

        using Index = typename PyramidBitset<max_k>::ValueType;
        constexpr u32 index_mask = std::numeric_limits<Index>::max();
        const auto is_free = pbs_make<max_k>(free_words);
        BusyHeap busy;
        u32 start = k - 1;
        const u32 horizon = arrival_data[num_requests - 1];
        const u32* const load_data = loads.data();
        pbs_initialize(is_free, kEmpty, k);

        u32 max_cnt = 1;
        u32 num_max_cnt = k;
        u32 num_free = 0;

        for (u32 i = 0; i != k; ++i)
        {
            cnt[i] = 1;
            const u32 finish = arrival_data[i] + load_data[i];
            const bool available = finish <= arrival_data[k];
            pbs_add_if(is_free, i & index_mask, available);
            num_free += available;
            if (!available & (finish <= horizon))
            {
                busy.push(finish, i);
            }
        }

        for (u32 request_index = k; request_index != num_requests;
             ++request_index)
        {
            ++start;
            start &= -u32{start != k};
            u32 arrival = arrival_data[request_index];

            while ((busy.size != 0) & (busy.time() <= arrival))
            {
                pbs_add(is_free, busy.pop() & index_mask);
                ++num_free;
            }

            if (num_free == 0)
            {
                if (busy.size == 0) break;
                continue;
            }

            u32 srv = pbs_next_inclusive(is_free, start & index_mask);
            if (srv >= k) srv = pbs_next_inclusive(is_free, 0u);
            pbs_remove(is_free, srv & index_mask);
            --num_free;
            u32 new_cnt = ++cnt[srv];
            num_max_cnt &= -u32{new_cnt <= max_cnt};
            max_cnt = std::max(new_cnt, max_cnt);
            num_max_cnt += new_cnt == max_cnt;

            u32 next_time_available = arrival + load_data[request_index];
            if (next_time_available <= horizon)
            {
                busy.push(next_time_available, srv);
            }
        }

        arrivals.clear();
        arrivals.resize(num_max_cnt);
        u32* out_data = arrivals.data();
        u32 out = 0;
        for (u32 i = 0; i != k; ++i)
        {
            if (cnt[i] == max_cnt) out_data[out++] = i;
        }
    }

    std::vector<int> busiestServers(
        u32 k,
        std::vector<int>& arrival,
        std::vector<int>& load) const noexcept
    {
        auto& arrivals = reinterpret_cast<std::vector<u32>&>(arrival);
        auto& loads = reinterpret_cast<std::vector<u32>&>(load);
        if (k <= 64)
        {
            impl<64>(k, arrivals, loads);
        }
        else if (k <= 4096)
        {
            impl<4096>(k, arrivals, loads);
        }
        else
        {
            impl<kCapacity>(k, arrivals, loads);
        }
        return std::move(arrival);
    }
};
