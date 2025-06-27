#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <optional>
#include <span>
#include <string>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

#ifdef __GNUC__
#define ATTR inline __attribute__((always_inline))
#else
#define ATTR inline
#endif

template <typename T, uint16_t C>
class SmallArray
{
public:
    constexpr SmallArray() noexcept = default;
    constexpr SmallArray(const SmallArray&) noexcept = default;
    constexpr SmallArray& operator=(const SmallArray&) noexcept = default;
    static constexpr auto capacity = C;
    [[nodiscard]] ATTR constexpr auto view() noexcept
    {
        return std::span{data_}.first(size_);
    }
    [[nodiscard]] ATTR constexpr auto view() const noexcept
    {
        return std::span{data_}.first(size_);
    }

    constexpr T& push_back(const T& v) noexcept { return (data_[size_++] = v); }
    [[nodiscard]] ATTR constexpr bool isFull() const noexcept
    {
        return size_ == capacity;
    }

    [[nodiscard]] ATTR constexpr std::optional<T> optLast() const noexcept
    {
        if (size_) return std::optional<T>{std::in_place, data_[size_ - 1]};
        return std::nullopt;
    }

    [[nodiscard]] ATTR constexpr const T& operator[](u16 idx) const noexcept
    {
        return data_[idx];
    }

    [[nodiscard]] ATTR constexpr u16 size() const noexcept { return size_; }
    void pop_back() { --size_; }

private:
    std::array<T, capacity> data_{};
    uint16_t size_ = 0;
};

class Solution
{
public:
    struct CharInfo
    {
        SmallArray<u16, 2000> indices;
        [[nodiscard]] u16 num() const noexcept { return indices.size(); }
    };

    [[nodiscard]] ATTR static constexpr u8 charToIdx(char c) noexcept
    {
        return (c - 'a') & 0xFF;
    }
    [[nodiscard]] ATTR static constexpr char idxToChar(u8 c) noexcept
    {
        return static_cast<char>(c + 'a');
    }

    [[nodiscard]] ATTR bool test_current() const noexcept
    {
        std::array<char, 7> chars{};

        for (u8 i = 0; i != current.size(); ++i) chars[i] = s[current[i]];

        size_t pos = 0;
        for (u16 ki = 0; ki != k; ++ki)
        {
            for (u8 j = 0; j != current.size(); ++j)
            {
                char c = chars[j];
                pos = s.find(c, pos);
                if (pos == s.npos) return false;
                ++pos;
            }
        }

        return true;
    }

    void dfs(u16 start)
    {
        for (u8 i = 0; i != sorted_info.size(); ++i)
        {
            auto& ci = *sorted_info[i];

            const u16* ci_idx = nullptr;
            for (u16 j = 0; j != ci.indices.size(); ++j)
            {
                if (const u16& v = ci.indices[j]; v >= start)
                {
                    ci_idx = &v;
                    break;
                }
            }

            if (ci_idx)
            {
                current.push_back(*ci_idx);
                if (test_current())
                {
                    if (current.size() > best.size())
                    {
                        best = current;
                        if (current.isFull()) throw 42;  // NOLINT
                    }

                    // Try this character
                    dfs(*ci_idx + 1);
                }
                current.pop_back();
            }
        }
    }

    [[nodiscard]] std::string longestSubsequenceRepeatedK(
        const std::string& s_,
        u16 k_) noexcept
    {
        s = s_;
        k = k_;
        current = {};
        best = {};

        std::array<CharInfo, 26> info{};
        for (u16 i = 0; i != s.size(); ++i)
        {
            info[charToIdx(s[i])].indices.push_back(i);
        }

        std::array<const CharInfo*, 26> pointers;  // NOLINT
        {
            for (size_t i = 0; i != info.size(); ++i)
            {
                pointers[i] = &info[i];
            }
            std::ranges::reverse(pointers);
            auto [ret, last] = std::ranges::remove_if(
                pointers,
                [&](const CharInfo* ci) { return ci->num() < k; });
            sorted_info = std::span{pointers.begin(), ret};
        }

        try
        {
            dfs(0);
        }
        catch (...)
        {
        }

        std::string result;
        for (u16 index : best.view()) result.push_back(s[index]);

        return result;
    }

    std::span<const CharInfo* const> sorted_info;  // NOLINT
    SmallArray<u16, 7> current{}, best{};
    std::string_view s;
    u16 k;
};
