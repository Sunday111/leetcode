#pragma once

// #pragma GCC optimize("O3")

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "force_inline.hpp"
#include "hot_path.hpp"

class Solution
{
public:
    using u8 = uint8_t;
    using u64 = uint64_t;

    static constexpr auto is_vowel_bitset = []
    {
        u64 bs = 0;
        for (char c : std::string_view{"aeiou"})
        {
            bs |= (u64{1} << (c - 64));
        }
        return bs;
    }();

    FORCE_INLINE HOT_PATH static constexpr bool is_vowel(u8 c) noexcept
    {
        assert(c >= 64);
        return is_vowel_bitset & (uint64_t{1} << (c - 64));
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH static constexpr u64 str_to_bstr(
        const std::string& str) noexcept
    {
        u64 r = 0;
        u8 l = str.length() & 0xFF;

        for (u8 i = 0; i != l; ++i)
        {
            r |= u64{std::bit_cast<u8>(str[i])} << (i * 8);
        }

        r |= u64{l} << 56;

        return r;
    }

    FORCE_INLINE HOT_PATH static constexpr void bstr_to_str(
        u64 bstr,
        std::string& s)
    {
        s.clear();
        u8 l = static_cast<u8>(bstr >> 56);
        s.reserve(l);
        for (u8 i = 0; i < l; ++i)
        {
            u8 c = (bstr >> (i * 8)) & 0xFF;
            s.push_back(static_cast<char>(c));
        }
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH static constexpr u64 to_lower(
        const u64 bstr) noexcept
    {
        u64 r = 0;

        for (u8 i = 0; i != 7; ++i)
        {
            u8 c = (bstr >> (8 * i)) & 0x7F;
            c = std::tolower(c) & 0x7F;
            r |= u64{std::bit_cast<u8>(c)} << (i * 8);
        }

        return r;
    }

    [[nodiscard]] FORCE_INLINE HOT_PATH static constexpr u64 remove_vowels(
        const u64 bstr) noexcept
    {
        u64 r = 0;

        for (u8 i = 0; i != 7; ++i)
        {
            u8 c = (bstr >> (8 * i)) & 0x7F;
            c = (c && is_vowel(c)) ? ' ' : c;
            r |= u64{std::bit_cast<u8>(c)} << (i * 8);
        }

        return r;
    }

    [[nodiscard]] static constexpr std::vector<std::string> spellchecker(
        std::vector<std::string>& wordlist,
        std::vector<std::string>& queries) noexcept
    {
        std::unordered_map<u64, std::vector<u64>> case_lookup;
        std::unordered_map<u64, u64> no_vowels_lookup;

        for (const std::string& word : wordlist)
        {
            u64 bstr = str_to_bstr(word);
            u64 lowered = to_lower(bstr);
            u64 no_vowels = remove_vowels(lowered);
            case_lookup[lowered].push_back(bstr);
            no_vowels_lookup.try_emplace(no_vowels, bstr);
        }

        for (std::string& query : queries)
        {
            u64 query_bstr = str_to_bstr(query);
            u64 lowered = to_lower(query_bstr);

            if (auto it = case_lookup.find(lowered); it != case_lookup.end())
            {
                // If there is no exact match, convert the first one
                if (!std::ranges::contains(it->second, query_bstr))
                {
                    bstr_to_str(it->second.front(), query);
                }

                continue;
            }

            if (auto it = no_vowels_lookup.find(remove_vowels(lowered));
                it != no_vowels_lookup.end())
            {
                bstr_to_str(it->second, query);
                continue;
            }

            query.clear();
        }

        return std::move(queries);
    }
};
