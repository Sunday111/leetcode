#include <cstdint>
#include <memory_resource>
#include <type_traits>
#include <unordered_map>
#include <vector>




// simplified std::exchange
template <typename T>
    requires std::is_trivially_copyable_v<T>
[[nodiscard, gnu::always_inline]] constexpr T exch(T& x, T new_value) noexcept
{
    T tmp = x;
    x = new_value;
    return tmp;
}


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
public:
    using u64 = uint64_t;
    u32 minJumps(std::vector<int>& a)
    {
        static auto pool = std::pmr::unsynchronized_pool_resource{};
        const u32 n = static_cast<u32>(a.size());

        // map from value to the head of linked list
        std::pmr::unordered_map<int, u32> head(&pool);
        head.reserve(2 * n);
        // previous index with the same value.
        // terminated with ~u32{}
        static u32 prev[50000];
        std::fill_n(prev, n, ~u32{});

        // build linked lists
        for (u32 i = 0; i != n; ++i)
        {
            auto it = head.try_emplace(a[i], ~u32{}).first;
            prev[i] = exch(it->second, i);
        }

        static u32 q[100000];
        u32 qb = 0, qe = 0;
        u64 f[783];
        std::fill_n(f, (n / 64) + 1, 0);

        auto enqueue = [&] [[nodiscard]] (u32 i)
        {
            q[qe] = i;
            qe += !(f[i >> 6] & (u64{1} << (i & 63)));
        };
        enqueue(0);

        for (u32 depth = 0; qb != qe; ++depth)
        {
            for (u32 stop = qe; qb != stop; ++qb)
            {
                // pop from the queue
                u32 i = q[qb];
                if (f[i >> 6] & (u64{1} << (i & 63))) continue;
                f[i >> 6] |= (u64{1} << (i & 63));

                // reached the last index?
                [[unlikely]] if (i + 1 == n)
                {
                    return depth;
                }

                // enqueue direct nighbours
                enqueue((i - 1) & -u32{!i});
                enqueue(i + 1);

                // walk the linked list to
                // enqueue indices with the same value
                i = exch(head[a[i]], ~u32{});
                while (i != ~u32{})
                {
                    enqueue(exch(i, prev[i]));
                }
            }
        }

        std::unreachable();
    }
};
