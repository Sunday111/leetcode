#include <algorithm>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <span>
#include <type_traits>
#include <utility>
#include <vector>






#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

template <
    u32 capacity,
    typename Value,
    auto empty_key,
    auto key_proj = std::identity{}>
    requires(std::popcount(capacity) == 1)
class HashSet
{
public:
    using Key = std::decay_t<decltype(key_proj(std::declval<Value>()))>;
    static constexpr u32 kHashMask = capacity - 1;
    static constexpr std::hash<std::decay_t<Key>> kHasher{};

    constexpr void Init() noexcept
    {
        Value empty{};
        key_proj(empty) = empty_key;
        std::ranges::fill(data_, empty);
    }

    FORCE_INLINE void add(const Value& v) noexcept
    {
        u32 index = kHasher(key_proj(v)) & kHashMask;
        while (has_value(data_[index]))
        {
            ++index;
            index &= kHashMask;
        }
        data_[index] = v;
    }

    template <typename U>
    FORCE_INLINE bool contains(const U& key) const noexcept
    {
        u32 index = kHasher(key) & kHashMask;
        while (has_value(data_[index]) && key_proj(data_[index]) != key)
        {
            ++index;
            index &= kHashMask;
        }
        return has_value(data_[index]) && key_proj(data_[index]) == key;
    }

    template <typename U>
    [[nodiscard]] FORCE_INLINE Value* find(const U& key) noexcept
    {
        u32 index = kHasher(key) & kHashMask;
        while (has_value(data_[index]) && key_proj(data_[index]) != key)
        {
            ++index;
            index &= kHashMask;
        }
        auto* p = &data_[index];
        return has_value(*p) && key_proj(*p) == key ? p : nullptr;
    }

    [[nodiscard]] FORCE_INLINE static constexpr bool has_value(
        const Value& v) noexcept
    {
        return key_proj(v) != empty_key;
    }

    std::span<Value, capacity> data_;
};




template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

inline static constexpr auto iif =
    []<std::integral T> [[nodiscard, gnu::always_inline]] (
        bool c,
        T a,
        std::type_identity_t<T> b) noexcept -> T
{
    return (a & cast<T>(-c)) + (b & cast<T>(~cast<T>(-c)));
};


using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

class Solution
{
public:
    [[nodiscard, gnu::always_inline]] static constexpr u32 pack(
        i16 a,
        i16 b) noexcept
    {
        return (u32{std::bit_cast<u16>(a)} << 16) | u32{std::bit_cast<u16>(b)};
    }

    int robotSim(
        const std::vector<int>& commands,
        std::vector<std::vector<int>>& in_obstacles)
    {
        static u32 data[1 << 14];
        HashSet<1 << 14, u32, ~u32{}> obstacles{data};
        obstacles.Init();

        for (auto& obstacle : in_obstacles)
        {
            obstacles.add(pack(
                static_cast<i16>(obstacle[0]),
                static_cast<i16>(obstacle[1])));
        }

        int dx = 0, dy = 1;
        int px = 0, py = 0;
        int max_dist_sq = 0;

        for (size_t i = 0; i != commands.size();)
        {
            int c = commands[i];
            if (c < 0)
            {
                std::swap(dx, dy);

                bool cw = c == -1;
                dy = iif(cw, -dy, dy);
                dx = iif(cw, dx, -dx);
                ++i;
                continue;
            }

            int command = 0;
            while (i != commands.size() && commands[i] > 0)
            {
                command += commands[i];
                ++i;
            }

            // move
            while (command != 0)
            {
                const int tx = px + dx, ty = py + dy;
                if (obstacles.contains(
                        pack(static_cast<i16>(tx), static_cast<i16>(ty))))
                {
                    break;
                }
                px = tx, py = ty;
                --command;
            }

            max_dist_sq = std::max(px * px + py * py, max_dist_sq);
        }

        return max_dist_sq;
    }
};
