#pragma once

#include <algorithm>
#include <bit>
#include <span>

#include "force_inline.hpp"
#include "integral_aliases.hpp"

template <
    u32 capacity,
    typename Value,
    auto empty_val,
    auto proj = std::identity{}>
    requires(std::popcount(capacity) == 1)
class HashSet
{
public:
    using Key = decltype(proj(std::declval<Value>()));
    static constexpr u32 kHashMask = capacity - 1;
    static constexpr std::hash<std::decay_t<Key>> kHasher{};

    constexpr void Init(const Value& v) noexcept
    {
        std::ranges::fill(data_, v);
    }

    FORCE_INLINE void add(const Value& v) noexcept
    {
        u32 index = kHasher(proj(v)) & kHashMask;
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
        while (has_value(data_[index]) && proj(data_[index]) != key)
        {
            ++index;
            index &= kHashMask;
        }
        return has_value(data_[index]) && proj(data_[index]) == key;
    }

    template <typename U>
    [[nodiscard]] FORCE_INLINE Value* find(const U& key) noexcept
    {
        u32 index = kHasher(key) & kHashMask;
        while (has_value(data_[index]) && proj(data_[index]) != key)
        {
            ++index;
            index &= kHashMask;
        }
        auto* p = &data_[index];
        return has_value(*p) && proj(*p) == key ? p : nullptr;
    }

    [[nodiscard]] FORCE_INLINE static constexpr bool has_value(
        const Value& v) noexcept
    {
        return proj(v) != empty_val;
    }

    std::span<Value, capacity> data_;
};
