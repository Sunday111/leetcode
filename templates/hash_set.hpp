#pragma once

#include <algorithm>
#include <bit>
#include <span>

#include "integral_aliases.hpp"

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

    [[gnu::always_inline]] inline void add(const Value& v) noexcept
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
    [[gnu::always_inline]] inline bool contains(const U& key) const noexcept
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
    [[nodiscard, gnu::always_inline]] inline Value* find(const U& key) noexcept
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

    [[nodiscard, gnu::always_inline]] inline static constexpr bool has_value(
        const Value& v) noexcept
    {
        return key_proj(v) != empty_key;
    }

    std::span<Value, capacity> data_;
};
