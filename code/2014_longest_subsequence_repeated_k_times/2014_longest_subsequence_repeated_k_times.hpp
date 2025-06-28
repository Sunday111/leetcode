#pragma once

#include <array>
#include <cassert>
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

        auto push_update = [&](u8 i, char push_char)
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
            if (!push_update(0, c0)) continue;

            for (char c1 : chars)
            {
                if (!push_update(1, c1)) continue;

                for (char c2 : chars)
                {
                    if (!push_update(2, c2)) continue;

                    for (char c3 : chars)
                    {
                        if (!push_update(3, c3)) continue;

                        for (char c4 : chars)
                        {
                            if (!push_update(4, c4)) continue;

                            for (char c5 : chars)
                            {
                                if (!push_update(5, c5)) continue;

                                for (char c6 : chars)
                                {
                                    if (push_update(6, c6))
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
