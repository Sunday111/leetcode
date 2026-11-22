#pragma once

#include <algorithm>
#include <cstring>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"
#include "radix_sorter.hpp"
#include "solution_name.hpp"
#include "sync_stdio.hpp"

class LC_SOLUTION_NAME(_adaptive)
{
    static constexpr u32 kWords = (1'000'001 + 63) / 64;
    inline static u64 present[kWords];
    inline static u64 duplicate[kWords];

    static void clear_occurrences(u32 first, u32 last)
    {
        std::memset(present + first, 0, (last - first + 1) * 8);
        std::memset(duplicate + first, 0, (last - first + 1) * 8);
    }

    static void add_occurrence(u32 x)
    {
        u32 word = x >> 6;
        u64 mask = u64{1} << (x & 63);
        if (duplicate[word] & mask) return;
        duplicate[word] |= present[word] & mask;
        present[word] |= mask;
    }

    [[gnu::always_inline]] static u32 pop_highest(u64& word)
    {
        u32 bit = 63 - cast<u32>(__builtin_clzll(word));
        word ^= u64{1} << bit;
        return bit;
    }

    static void for_each_distinct_descending(u32 first, u32 last, auto&& visit)
    {
        for (u32 i = last + 1; i-- != first;)
        {
            u64 word = present[i];
            while (word)
            {
                u32 bit = pop_highest(word);
                visit((i << 6) | bit, (duplicate[i] & (u64{1} << bit)) != 0);
            }
        }
    }

    [[gnu::always_inline]] static u32 max(u32 a, u32 b)
    {
        return a > b ? a : b;
    }

    static u32 sorted(u32* data, u32 n)
    {
        u32 previous = 0, keep = 0, increment = 0, answer = 0;
        for (auto* p = data + n; p != data;)
        {
            u32 x = *--p;
            u32 d = previous - x;
            u32 next_keep =
                1 + (increment & -u32{d == 0}) + (keep & -u32{d == 1});
            u32 next_increment =
                d == 0 ? increment
                       : 1 + (increment & -u32{d == 1}) + (keep & -u32{d == 2});
            previous = x;
            keep = next_keep;
            increment = next_increment;
            answer = max(answer, max(keep, increment));
        }
        return answer;
    }

public:
    [[gnu::flatten, gnu::target("avx2,bmi,bmi2,lzcnt,popcnt")]]
    static u32 maxSelectedElements(std::vector<int>& nums) noexcept
    {
        auto* data = reinterpret_cast<u32*>(nums.data());
        u32 n = cast<u32>(nums.size());
        if (n <= 128)
        {
            std::sort(data, data + n);
            return sorted(data, n);
        }

        u32 low = 1'000'000, high = 0;
        for (u32 i = 0; i != n; ++i)
        {
            u32 x = data[i];
            low = std::min(low, x);
            high = max(high, x);
        }
        if (low == high) return 2;

        u32 first = low >> 6, last = high >> 6;
        if (n < 32'768 && last - first + 1 > n / 4)
        {
            radix_sort<10, 2>(data, n);
            return sorted(data, n);
        }

        clear_occurrences(first, last);
        for (u32 i = 0; i != n; ++i) add_occurrence(data[i]);

        u32 previous = 0, keep = 0, increment = 0, answer = 0;
        for_each_distinct_descending(
            first,
            last,
            [&] [[gnu::always_inline]] (u32 x, bool repeated)
            {
                u32 d = previous - x;
                u32 next_keep = 1 + (keep & -u32{d == 1});
                u32 next_increment =
                    1 + (increment & -u32{d == 1}) + (keep & -u32{d == 2});
                keep = repeated ? next_increment + 1 : next_keep;
                increment = next_increment;
                previous = x;
                answer = max(answer, max(keep, increment));
            });
        return answer;
    }
};
