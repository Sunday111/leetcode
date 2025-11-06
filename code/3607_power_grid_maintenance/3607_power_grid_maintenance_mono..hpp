#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <span>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

#define HOT_PATH __attribute__((hot))

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

#define NO_SANITIZERS \
    __attribute__((no_sanitize("undefined", "address", "coverage", "thread")))

template <typename To, typename From, std::size_t extent = std::dynamic_extent>
    requires(sizeof(To) == sizeof(From))
[[nodiscard]] FORCE_INLINE static auto reinterpret_range(
    std::span<From, extent> in) noexcept
{
    return std::span<To, extent>{
        reinterpret_cast<To*>(in.data()),  // NOLINT
        in.size()};
}

template <typename To, typename From, typename Allocator>
    requires(sizeof(To) == sizeof(From))
[[nodiscard]] FORCE_INLINE static std::span<To> reinterpret_range(
    std::vector<From, Allocator>& v) noexcept
{
    return reinterpret_range<To>(std::span{v});
}

enum class SortOrder : u8
{
    Ascending,
    Descending
};

template <
    std::integral T,
    SortOrder order,
    bool stable,
    u8 bits_per_pass,
    u32 num_passes = ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)>
    requires(((num_passes * bits_per_pass) <= sizeof(T) * 8) && (sizeof(T) > 1))
class RadixSorter
{
    using UT = std::make_unsigned_t<T>;

    static constexpr UT base = 1u << bits_per_pass;
    static constexpr UT mask = base - 1;
    static constexpr auto pass_idx_seq =
        std::make_integer_sequence<u8, num_passes>();
    static constexpr size_t num_bits = sizeof(T) * 8;

    inline static std::array<UT, base> count;
    inline static std::array<UT, 100'001> temp;

    template <u8 pass_index>
    FORCE_INLINE static void do_pass(std::span<UT> arr) noexcept
        NO_SANITIZERS HOT_PATH
    {
        count.fill(0);
        constexpr UT shift = pass_index * bits_per_pass;
        constexpr UT msb = UT{1} << (num_bits - 1);
        constexpr bool sign_masking = std::is_signed_v<T>;
        constexpr bool is_first_pass = pass_index == 0;
        constexpr bool is_last_pass = (pass_index == (num_passes - 1));
        constexpr UT pre_sign_mask = sign_masking && is_first_pass ? msb : UT{};
        constexpr UT post_sign_mask = sign_masking && is_last_pass ? msb : UT{};

        // Count digit occurrences
        for (auto& v : arr)
        {
            v ^= pre_sign_mask;
            ++count[(v >> shift) & mask];
        }

        const u32 n = static_cast<u32>(arr.size());

        if constexpr (order == SortOrder::Ascending)
        {
            if constexpr (stable)
            {
                std::inclusive_scan(count.begin(), count.end(), count.begin());

                for (u32 i = n; i--;)
                {
                    UT digit = (arr[i] >> shift) & mask;
                    temp[--count[digit]] = arr[i] ^ post_sign_mask;
                }
            }
            else
            {
                std::exclusive_scan(
                    count.begin(),
                    count.end(),
                    count.begin(),
                    0);

                for (u32 j = 0; j != n; ++j)
                {
                    UT v = arr[j];
                    temp[count[(v >> shift) & mask]++] = v ^ post_sign_mask;
                }
            }
        }
        else  // Descending
        {
            // Compute descending start positions
            std::exclusive_scan(
                count.rbegin(),
                count.rend(),
                count.rbegin(),
                UT{0});

            for (u32 i = 0; i != n; ++i)
            {
                UT v = (arr[i] >> shift) & mask;
                temp[count[v]++] = arr[i] ^ post_sign_mask;
            }
        }

        std::ranges::copy_n(temp.begin(), n, arr.begin());
    }

    // Invokes do_pass for each pass_index.
    template <u8... pass_index>
    FORCE_INLINE static void do_passes(
        std::span<UT> arr,
        std::integer_sequence<u8, pass_index...>) noexcept
        NO_SANITIZERS HOT_PATH
    {
        (do_pass<pass_index>(arr), ...);
    }

public:
    FORCE_INLINE static void sort(std::span<T> arr) noexcept
        NO_SANITIZERS HOT_PATH
    {
        if (arr.size()) do_passes(reinterpret_range<UT>(arr), pass_idx_seq);
    }
};

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    SortOrder order = SortOrder::Ascending,
    std::integral T>
FORCE_INLINE void radix_sort(std::span<T> arr) noexcept NO_SANITIZERS
{
    constexpr u32 np =
        num_passes == 0xFFFFFFFF
            ? ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)
            : num_passes;
    RadixSorter<T, order, false, bits_per_pass, np>::sort(arr);
}

template <
    u8 bits_per_pass,
    u32 num_passes = 0xFFFFFFFF,
    SortOrder order = SortOrder::Ascending,
    std::integral T>
FORCE_INLINE void stable_radix_sort(std::span<T> arr) noexcept NO_SANITIZERS
{
    constexpr u32 np =
        num_passes == 0xFFFFFFFF
            ? ((sizeof(T) * 8 + bits_per_pass - 1) / bits_per_pass)
            : num_passes;
    RadixSorter<T, order, true, bits_per_pass, np>::sort(arr);
}

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

struct GroupInfo
{
    u32 end = 0;
    u32 begin = 0;
};

struct Node
{
    u32 offset = 0;
    u32 num_links = 0;
};

class Solution
{
public:
    void processQueries(
        u32 c,
        std::vector<std::vector<u32>>& connections,
        std::vector<std::vector<u32>>& queries,
        std::vector<u32>& result)
    {
        Node nodes[100'002];
        u32 child_array[200'004];
        std::fill_n(nodes, c + 1, Node{});

        for (auto& connection : connections)
        {
            u32 a = connection[0], b = connection[1];
            nodes[a].num_links++;
            nodes[b].num_links++;
        }

        for (u32 offset = 0, node_id = 1; node_id <= c; ++node_id)
        {
            auto& node = nodes[node_id];
            node.offset = offset;
            offset += std::exchange(node.num_links, 0);
        }

        for (auto& connection : connections)
        {
            u32 aid = connection[0], bid = connection[1];
            auto &a = nodes[aid], &b = nodes[bid];
            child_array[a.offset + a.num_links++] = bid;
            child_array[b.offset + b.num_links++] = aid;
        }

        static u32 nodes_groups[100'002];
        std::fill_n(nodes_groups, c + 1, 0u);

        static u32 groups_nodes_arr[100'002];
        u32 groups_nodes_arr_offset = 0;

        std::vector<GroupInfo> groups;
        groups.emplace_back();

        static u32 q[100'002];
        u32 qs = 0;

        u32 next_group = 1;

        for (u32 i = 1; i <= c; ++i)
        {
            if (nodes_groups[i]) continue;
            u32 group_id = next_group++;
            auto& group = groups.emplace_back();
            group.end = group.begin = groups_nodes_arr_offset;

            q[qs++] = i;

            while (qs)
            {
                auto node_id = q[--qs];
                if (nodes_groups[node_id]) continue;
                nodes_groups[node_id] = group_id;
                groups_nodes_arr[group.end++] = node_id;

                auto& node = nodes[node_id];
                u32 child_idx = node.offset;
                u32 end = child_idx + node.num_links;
                while (child_idx != end) q[qs++] = child_array[child_idx++];
            }

            groups_nodes_arr_offset = group.end;
        }

        for (auto& group : groups)
        {
            radix_sort<4>(std::span{
                groups_nodes_arr + group.begin,
                groups_nodes_arr + group.end});
        }

        result.reserve(queries.size());
        std::vector<bool> status(c + 1, true);
        for (auto& query : queries)
        {
            u32 station = query[1];
            u32 group_id = nodes_groups[station];
            auto& group = groups[group_id];
            if (query[0] == 1)
            {
                u32& ans = result.emplace_back(0xFFFFFFFF);
                if (status[station])
                {
                    ans = station;
                }
                else
                {
                    while (group.begin != group.end &&
                           !status[groups_nodes_arr[group.begin]])
                    {
                        ++group.begin;
                    }

                    if (group.begin != group.end)
                    {
                        ans = groups_nodes_arr[group.begin];
                    }
                }
            }
            else if (status[station])
            {
                status[station] = false;
            }
        }
    }

    std::vector<int> processQueries(
        u32 c,
        std::vector<std::vector<int>>& connections,
        std::vector<std::vector<int>>& queries)
    {
        std::vector<int> result;
        processQueries(
            c,
            reinterpret_cast<std::vector<std::vector<u32>>&>(connections),
            reinterpret_cast<std::vector<std::vector<u32>>&>(queries),
            reinterpret_cast<std::vector<u32>&>(result));
        return result;
    }
};
