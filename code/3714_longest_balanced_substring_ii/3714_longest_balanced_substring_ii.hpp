#include <algorithm>
#include <array>
#include <unordered_map>
#include <vector>

#include "bump_allocator.hpp"
#include "integral_aliases.hpp"

#define HOT_PATH __attribute__((hot))

using SolutionStorage = GlobalBufferStorage<1 << 25>;

class Solution
{
public:
    using u8 = uint8_t;
    using u32 = uint32_t;

    using Cnt = std::array<u32, 3>;
    std::vector<Cnt, BumpAllocator<Cnt, SolutionStorage>> freq{};
    u32 n = 0;

    [[nodiscard]] static u32 one_char(char target, std::string_view s) noexcept
        HOT_PATH NO_SANITIZERS
    {
        u32 l = 0, r = 0;
        for (char c : s)
        {
            r = std::max(r, l);
            u32 b = c != target;
            l &= (b - 1);
            l += !b;
        }

        return std::max(r, l);
    }

    [[nodiscard]] u32 two_chars(char c1, char c2, char c3)
        const noexcept HOT_PATH NO_SANITIZERS
    {
        const auto scoped_arena = SolutionStorage::Instance().StartArena();

        ObjectWithoutDtor<std::unordered_map<
            u32,
            u32,
            std::hash<u32>,
            std::equal_to<u32>,
            BumpAllocator<std::pair<const u32, u32>, SolutionStorage>>>
            diff_to_idx;
        u32 r = 0;
        const u8 u1 = (c1 - 'a') & 0x1F, u2 = (c2 - 'a') & 0x1F,
                 u3 = (c3 - 'a') & 0x1F;

        u32 split_c1c2 = 0, split_c3 = 0;
        for (u32 i = 0, l = 1; i != n; ++i, ++l)
        {
            const auto& f = freq[i];
            if (f[u3] != split_c3)
            {
                l = 0;
                split_c1c2 = f[u1] - f[u2], split_c3 = f[u3];
                diff_to_idx.Reset();
                continue;
            }

            u32 t = 0;
            if (u32 diff = f[u1] - f[u2] - split_c1c2)
            {
                auto [it, inserted] = diff_to_idx->try_emplace(diff, i);
                t = (inserted - 1) & (i - it->second);
            }
            else
            {
                t = l;
            }
            r = std::max(r, t);
        }

        return r;
    }

    [[nodiscard]] u32 three_chars() const noexcept HOT_PATH NO_SANITIZERS
    {
        const auto scoped_arena = SolutionStorage::Instance().StartArena();

        ObjectWithoutDtor<std::unordered_map<
            u64,
            u32,
            std::hash<u64>,
            std::equal_to<u64>,
            BumpAllocator<std::pair<const u64, u32>, SolutionStorage>>>
            diff_to_idx;
        u32 r = 0;

        for (u32 i = 0; i != n; ++i)
        {
            const auto& [fa, fb, fc] = freq[i];
            u32 t = 0;
            if (u32 d1 = fa - fb, d2 = fc - fa; d1 | d2)
            {
                u64 key = (u64{d1} << 32) | u64{d2};
                auto [it, inserted] = diff_to_idx->try_emplace(key, i);
                t = (inserted - 1) & (i - it->second);
            }
            else
            {
                t = i + 1;
            }
            r = std::max(r, t);
        }

        return r;
    }

    [[nodiscard]] u32 longestBalanced(const std::string& s) noexcept HOT_PATH
        NO_SANITIZERS
    {
        const auto scoped_arena = SolutionStorage::Instance().StartArena();

        n = static_cast<u32>(s.size());

        freq.reserve(n);
        freq.emplace_back()[(s[0] - 'a') & 0x1F]++;

        for (u32 i = 1; i != n; ++i)
        {
            auto f = freq.back();
            ++f[(s[i] - 'a') & 0x1F];
            freq.push_back(f);
        }

        u32 r = 0;
        r = std::max(r, one_char('a', s));
        r = std::max(r, one_char('b', s));
        r = std::max(r, one_char('c', s));
        r = std::max(r, two_chars('a', 'b', 'c'));
        r = std::max(r, two_chars('b', 'c', 'a'));
        r = std::max(r, two_chars('a', 'c', 'b'));
        r = std::max(r, three_chars());
        return r;
    }
};

#include "sync_stdio.hpp"
