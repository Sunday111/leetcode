#pragma once

#include <algorithm>
#include <array>
#include <cassert>
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

class Solution
{
public:
    [[nodiscard]] ATTR static constexpr u8 charToIdx(char c) noexcept { return (c - 'a') & 0xFF; }
    [[nodiscard]] ATTR static constexpr char idxToChar(u8 c) noexcept { return static_cast<char>(c + 'a'); }

    [[nodiscard]] ATTR static constexpr std::string longestSubsequenceRepeatedK(std::string& s, u16 k) noexcept
    {
        // prepare lookup info
        std::array<u16, 26> freq{};
        const std::string chars = [&]
        {
            for (char c : s) freq[charToIdx(c)]++;

            // remove chars with freq < k
            u16 n = 0;
            for (char c : s)
            {
                u8 ci = charToIdx(c);
                if (freq[ci] >= k) s[n++] = c;
            }
            s.resize(n);

            // unique chars
            std::string chars;
            u8 ci = freq.size();
            do
            {
                --ci;
                if (freq[ci] >= k)
                {
                    chars.push_back(idxToChar(ci));
                }
            } while (ci != 0);

            return chars;
        }();

        std::string current, best;

        auto pushUpdate = [&](u8 i, char push_char)
        {
            const u8 ci = charToIdx(push_char);
            if (freq[ci] < k) return false;

            current.resize(i);
            current.push_back(push_char);

            // Find current subsequence k times in s
            size_t end = 0;
            for (u16 ki = 0; ki != k; ++ki)
            {
                for (char c : current)
                {
                    end = s.find(c, end);
                    if (end >= s.size()) return false;
                    ++end;
                }
            }

            // only update best if validation above succeeded
            if (current.size() > best.size()) best = current;

            freq[ci] -= k;
            return true;
        };

        for (char c0 : chars)
        {
            if (!pushUpdate(0, c0)) continue;

            for (char c1 : chars)
            {
                if (!pushUpdate(1, c1)) continue;

                for (char c2 : chars)
                {
                    if (!pushUpdate(2, c2)) continue;

                    for (char c3 : chars)
                    {
                        if (!pushUpdate(3, c3)) continue;

                        for (char c4 : chars)
                        {
                            if (!pushUpdate(4, c4)) continue;

                            for (char c5 : chars)
                            {
                                if (!pushUpdate(5, c5)) continue;

                                for (char c6 : chars)
                                {
                                    if (pushUpdate(6, c6))
                                    {
                                        return best;
                                    }
                                }
                                freq[charToIdx(c5)] += k;
                            }
                            freq[charToIdx(c4)] += k;
                        }
                        freq[charToIdx(c3)] += k;
                    }
                    freq[charToIdx(c2)] += k;
                }
                freq[charToIdx(c1)] += k;
            }
            freq[charToIdx(c0)] += k;
        }

        return best;
    }
};

class Solution2
{
public:
    [[nodiscard]] ATTR static constexpr u8 charToIdx(char c) noexcept { return (c - 'a') & 0xFF; }
    [[nodiscard]] ATTR static constexpr char idxToChar(u8 c) noexcept { return static_cast<char>(c + 'a'); }
    [[nodiscard]] ATTR static constexpr const u16* find_ge(u16* indices, u16 num, u16 start) noexcept
    {
        for (u16 j = 0; j != num; ++j)
        {
            if (const u16& v = indices[j]; v >= start)  // NOLINT
            {
                return &v;
            }
        }

        return nullptr;
    }

    [[nodiscard]] ATTR static constexpr std::string longestSubsequenceRepeatedK(std::string& s, u16 k) noexcept
    {
        struct CharInfo
        {
            u16* indices{};
            u16 num{};
        };

        std::array<u16, 26> freq;           // NOLINT
        std::array<CharInfo, 26> all_info;  // NOLINT
        std::array<u16, 2000> all_indices;  // NOLINT
        std::span<const CharInfo> sorted_info;

        // prepare lookup table
        {
            // collect num entries
            for (char c : s) all_info[charToIdx(c)].num++;

            u16 next_s = 0;
            for (char c : s)
            {
                u8 ci = charToIdx(c);
                if (all_info[ci].num >= k) s[next_s++] = c;
            }
            s.resize(next_s);

            // init first pointer for each char indices list
            u16* next = all_indices.data();
            for (auto& ci : all_info)
            {
                ci.indices = next;
                next += ci.num;  // NOLINT
                ci.num = 0;      // <- reset this, accumulate again below
            }

            for (u16 i = 0; i != s.size(); ++i)
            {
                auto& ci = all_info[charToIdx(s[i])];
                ci.indices[ci.num++] = i;  // NOLINT
            }

            for (u8 i = 0; i != freq.size(); ++i)
            {
                freq[i] = all_info[i].num;
            }

            std::ranges::reverse(all_info);
            auto [ret, last] = std::ranges::remove_if(all_info, [&](const CharInfo& ci) { return ci.num < k; });
            auto sorted = std::span{all_info.begin(), ret};
            sorted_info = sorted;

            for (auto& i : sorted) i.num -= k - 1;
        }

        std::array<u16, 7> current, best;  // NOLINT
        u8 num_current = 0, num_best = 0;

        std::array<char, 7> current_chars{};

        auto to_string = [&]
        {
            std::string result;
            for (u16 index : std::span{best}.first(num_best)) result.push_back(s[index]);
            return result;
        };

        auto pushUpdate = [&](u8 i, const u16* v)
        {
            if (!v) return false;

            num_current = i + 1;
            current[i] = *v;
            current_chars[i] = s[*v];

            u8 ci = charToIdx(current_chars[i]);
            if (freq[ci] < k) return false;

            // Find current subsequence k times in s
            size_t end = 0;
            for (u16 ki = 0; ki != k; ++ki)
            {
                for (u8 j = 0; j != num_current; ++j)
                {
                    end = s.find(current_chars[j], end);
                    if (end == s.npos) return false;
                    ++end;
                }
            }

            // only update best if validation above succeeded
            if (num_current > num_best)
            {
                best = current;
                num_best = num_current;
            }

            freq[ci] -= k;

            return true;
        };

        for (auto& si0 : sorted_info)
        {
            if (!pushUpdate(0, &si0.indices[0])) continue;

            for (auto& si1 : sorted_info)
            {
                auto pi1 = find_ge(si1.indices, si1.num, current[0]);
                if (!pushUpdate(1, pi1)) continue;

                for (auto& si2 : sorted_info)
                {
                    auto pi2 = find_ge(si2.indices, si2.num, *pi1);
                    if (!pushUpdate(2, pi2)) continue;

                    for (auto& si3 : sorted_info)
                    {
                        auto pi3 = find_ge(si3.indices, si3.num, *pi2);
                        if (!pushUpdate(3, pi3)) continue;

                        for (auto& si4 : sorted_info)
                        {
                            auto pi4 = find_ge(si4.indices, si4.num, *pi3);
                            if (!pushUpdate(4, pi4)) continue;

                            for (auto& si5 : sorted_info)
                            {
                                auto pi5 = find_ge(si5.indices, si5.num, *pi4);
                                if (!pushUpdate(5, pi5)) continue;

                                for (auto& si6 : sorted_info)
                                {
                                    auto pi6 = find_ge(si6.indices, si6.num, *pi5);
                                    if (pushUpdate(6, pi6))
                                    {
                                        best = current;
                                        return to_string();
                                    }
                                    freq[charToIdx(current_chars[6])] += k;
                                }
                                freq[charToIdx(current_chars[5])] += k;
                            }
                            freq[charToIdx(current_chars[4])] += k;
                        }
                        freq[charToIdx(current_chars[3])] += k;
                    }
                    freq[charToIdx(current_chars[2])] += k;
                }
                freq[charToIdx(current_chars[1])] += k;
            }
            freq[charToIdx(current_chars[0])] += k;
        }

        return to_string();
    }
};

class Solution3
{
public:
    [[nodiscard]] ATTR static constexpr u8 charToIdx(char c) noexcept { return (c - 'a') & 0xFF; }
    [[nodiscard]] ATTR static constexpr char idxToChar(u8 c) noexcept { return static_cast<char>(c + 'a'); }

    template <u8 v>
    using IC = std::integral_constant<u8, v>;
    template <u8 v>
    static constexpr auto kIC = IC<v>{};

    std::array<u16, 26> freq{};
    std::array<u16, 2000> find_cache{};
    std::string current, best;
    std::string_view s;
    u16 k;

    [[nodiscard]] constexpr u16 progSum(u16 num) noexcept { return ((1 + num) * num) / 2; }

    template <u8 depth>
    [[nodiscard]] ATTR constexpr bool pushUpdate(IC<depth>, char push_char) noexcept
    {
        const u8 ci = charToIdx(push_char);
        if (freq[ci] < k) return false;

        const u16 find_cache_begin = progSum(depth) * k;

        if constexpr (depth != 0)
        {
            // [indices for k == 0][indices for k == 1] ...
            const u16 prev_depth_cache_begin = progSum(depth - 1) * k;
            u16 from = prev_depth_cache_begin;
            u16 to = find_cache_begin;
            for (u16 i = 0; i != k; ++i)
            {
                for (u16 j = 0; j != depth; ++j)
                {
                    find_cache[to++] = find_cache[from++];
                }

                // This level has one more index. It has to start from the previous one at least
                find_cache[to] = find_cache[to - 1];
                to++;
            }
        }

        current.resize(depth);
        current.push_back(push_char);

        // Find current subsequence k times in s
        u16 fci = find_cache_begin;
        u16 end = 0;
        for (u16 ki = 0; ki != k; ++ki)
        {
            for (u8 char_idx = 0; char_idx != depth + 1; ++char_idx)
            {
                u16& find_pos = find_cache[fci++];
                find_pos = std::max(find_pos, end);
                find_pos = std::min(s.find(current[char_idx], find_pos), s.size()) & 0xFFFF;
                if (find_pos == s.size()) return false;
                end = find_pos + 1;
            }
        }

        // only update best if validation above succeeded
        if (current.size() > best.size()) best = current;

        freq[ci] -= k;
        return true;
    }

    [[nodiscard]] ATTR constexpr std::string longestSubsequenceRepeatedK(std::string& s_, u16 k_) noexcept
    {
        // prepare lookup info
        k = k_;
        const std::string chars = [&]
        {
            for (char c : s_) freq[charToIdx(c)]++;

            // remove chars with freq < k
            u16 n = 0;
            for (char c : s_)
            {
                u8 ci = charToIdx(c);
                if (freq[ci] >= k) s_[n++] = c;
            }
            s_.resize(n);
            s = s_;

            // unique chars
            std::string chars;
            u8 ci = freq.size() & 0xFF;
            do
            {
                --ci;
                if (freq[ci] >= k)
                {
                    chars.push_back(idxToChar(ci));
                }
            } while (ci != 0);

            return chars;
        }();

        for (char c0 : chars)
        {
            std::ranges::fill_n(find_cache.begin(), k, 0);
            if (!pushUpdate(kIC<0>, c0)) continue;

            for (char c1 : chars)
            {
                if (!pushUpdate(kIC<1>, c1)) continue;

                for (char c2 : chars)
                {
                    if (!pushUpdate(kIC<2>, c2)) continue;

                    for (char c3 : chars)
                    {
                        if (!pushUpdate(kIC<3>, c3)) continue;

                        for (char c4 : chars)
                        {
                            if (!pushUpdate(kIC<4>, c4)) continue;

                            for (char c5 : chars)
                            {
                                if (!pushUpdate(kIC<5>, c5)) continue;

                                for (char c6 : chars)
                                {
                                    if (pushUpdate(kIC<6>, c6))
                                    {
                                        return best;
                                    }
                                }
                                freq[charToIdx(c5)] += k;
                            }
                            freq[charToIdx(c4)] += k;
                        }
                        freq[charToIdx(c3)] += k;
                    }
                    freq[charToIdx(c2)] += k;
                }
                freq[charToIdx(c1)] += k;
            }
            freq[charToIdx(c0)] += k;
        }

        return best;
    }
};
