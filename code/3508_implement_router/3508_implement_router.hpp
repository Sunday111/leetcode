#include <algorithm>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

template <typename T>
[[nodiscard]] FORCE_INLINE constexpr size_t get_hash(const T& v) noexcept
{
    return std::hash<T>{}(v);
}

FORCE_INLINE void hash_combine(std::size_t& seed, std::size_t h) noexcept
{
    seed ^= h + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename... T>
[[nodiscard]] FORCE_INLINE constexpr size_t hash_combine(
    const T&... arg) noexcept
    requires((true && ... && std::same_as<T, size_t>))
{
    size_t r = 0;
    (hash_combine(r, arg), ...);
    return r;
}

template <typename... T>
[[nodiscard]] FORCE_INLINE constexpr size_t hash_together(T&&... arg) noexcept
{
    return hash_combine(get_hash(std::forward<T>(arg))...);
}

struct TupleHasher
{
    template <typename... T>
    FORCE_INLINE constexpr size_t operator()(
        const std::tuple<T...>& t) const noexcept
    {
        using Tuple = std::tuple<T...>;
        constexpr size_t n = std::tuple_size_v<Tuple>;
        return [&]<size_t... index>(std::index_sequence<index...>)
        {
            return hash_together(std::get<index>(t)...);
        }(std::make_index_sequence<n>());
    }
};

template <typename T>
class CircularArray
{
public:
    std::vector<T> data;
    size_t capacity = 0;
    size_t offset = 0;
};

class Router
{
public:
    using u32 = uint32_t;

    u32 capacity_ = 0;

    // Destinations in order of packets arrival
    std::array<u32, 100'001> order;
    u32 order_front = 0, order_back = 0;

    // for duplicates
    std::unordered_set<std::tuple<u32, u32, u32>, TupleHasher> all_;

    // key is destination
    // value is deque of packets. Pair is [source, time]
    std::unordered_map<u32, std::deque<std::pair<u32, u32>>> dst_to_st_;

    explicit Router(u32 capacity) : capacity_(capacity)  // NOLINT
    {
        all_.reserve(capacity_);
    }

    std::vector<int> result;

    [[nodiscard]] constexpr bool
    addPacket(u32 source, u32 destination, u32 time) noexcept
    {
        // duplicate?
        if (all_.contains({source, destination, time})) return false;

        all_.insert({source, destination, time});
        order[order_back++] = destination;
        dst_to_st_[destination].emplace_back(source, time);

        if (all_.size() > capacity_)
        {
            // delete oldest
            u32 oldest_dst = order[order_front++];
            auto [oldest_src, oldest_time] = dst_to_st_[oldest_dst].front();
            dst_to_st_[oldest_dst].pop_front();
            all_.erase({oldest_src, oldest_dst, oldest_time});
        }

        return true;
    }

    [[nodiscard]] constexpr const std::vector<int>& forwardPacket() noexcept
    {
        if (order_front != order_back)
        {
            u32 oldest_dst = order[order_front++];
            auto [oldest_src, oldest_time] = dst_to_st_[oldest_dst].front();
            dst_to_st_[oldest_dst].pop_front();
            all_.erase({oldest_src, oldest_dst, oldest_time});
            result = {
                static_cast<int>(oldest_src),
                static_cast<int>(oldest_dst),
                static_cast<int>(oldest_time),
            };
        }
        else
        {
            result.clear();
        }

        return result;
    }

    [[nodiscard]] constexpr int
    getCount(u32 destination, u32 startTime, u32 endTime) const noexcept
    {
        int r = 0;

        if (auto it = dst_to_st_.find(destination); it != dst_to_st_.end())
        {
            auto& dst_packets = it->second;
            constexpr auto proj = &std::pair<u32, u32>::second;
            auto lo = std::ranges::lower_bound(
                dst_packets,
                startTime,
                std::less{},
                proj);
            auto hi = std::ranges::upper_bound(
                lo,
                dst_packets.end(),
                endTime,
                std::less{},
                proj);

            r = static_cast<int>(std::distance(lo, hi));
        }

        return r;
    }
};
