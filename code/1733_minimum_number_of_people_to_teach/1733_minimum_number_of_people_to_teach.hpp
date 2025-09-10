#pragma once

#include <bitset>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

template <std::integral T>
[[nodiscard]] FORCE_INLINE static constexpr T ceil_div(T a, T b) noexcept
{
    return ((a + b) - 1) / b;
}

// Returns new end
template <typename ForwardIt, typename UnaryPredicate>
[[nodiscard]] static constexpr ForwardIt
unstable_remove_if(ForwardIt begin, ForwardIt end, UnaryPredicate p) noexcept
{
    while (begin != end)
    {
        if (p(*begin))
        {
            do
            {
                if (--end == begin) return begin;
            } while (p(*end));
            std::iter_swap(begin, end);
        }
        ++begin;
    }
    return end;
}

using u8 = uint8_t;
using u16 = uint16_t;

class Solution
{
public:
    template <u16 max_langs>
    [[nodiscard]] FORCE_INLINE static constexpr u16 test_languages(
        std::vector<std::vector<int>>& friendships,
        std::array<std::bitset<max_langs>, 512>& know,
        std::bitset<max_langs>& languages,
        u16 n,
        u16 max_r) noexcept
    {
        u16 r = max_r;
        for (u16 lang = 1; lang <= n; ++lang)
        {
            if (languages[lang])
            {
                u16 cnt = 0;
                std::bitset<512> learners;
                for (u16 f = 0; f != friendships.size() && cnt < max_r; ++f)
                {
                    auto& friendship = friendships[f];
                    u16 a = friendship[0] & 0xFFFF;
                    u16 b = friendship[1] & 0xFFFF;
                    bool prev_a = learners[a];
                    bool prev_b = learners[b];
                    bool new_a = prev_a || !know[a][lang];
                    bool new_b = prev_b || !know[b][lang];
                    cnt += new_a != prev_a;
                    cnt += new_b != prev_b;
                    learners[a] = new_a;
                    learners[b] = new_b;
                }
                r = std::min(cnt, r);
            }
        }

        return r;
    }

    template <u16 max_langs>
    [[nodiscard]] static constexpr u16 minimumTeachingsT1(
        u16 n,
        std::vector<std::vector<int>>& languages,
        std::vector<std::vector<int>>& friendships) noexcept
    {
        const u16 num_users = languages.size() & 0xFFFF;

        std::array<std::bitset<max_langs>, 512> know{};
        for (u16 user = 0; user != num_users; ++user)
        {
            auto& user_langs = know[user];
            for (int lang : languages[user]) user_langs[lang & 0xFFFF] = true;
        }

        // Filter out friendships that do not need fixing
        friendships.erase(
            unstable_remove_if(
                friendships.begin(),
                friendships.end(),
                [&](std::vector<int>& friendship)
                {
                    u16 a = (--friendship[0]) & 0xFFFF,
                        b = (--friendship[1]) & 0xFFFF;
                    return (know[a] & know[b]).count();
                }),
            friendships.end());

        if (friendships.empty()) return 0;

        auto or_langs =
            know[friendships[0][0] & 0xFFFF] ^ know[friendships[0][1] & 0xFFFF];
        auto and_langs = or_langs;

        for (u16 f = 1; f != friendships.size(); ++f)
        {
            auto tmp = know[friendships[f][0] & 0xFFFF] ^
                       know[friendships[f][1] & 0xFFFF];
            and_langs &= tmp;
            or_langs |= tmp;
        }

        u16 r = test_languages<max_langs>(
            friendships,
            know,
            and_langs,
            n,
            num_users);
        or_langs &= ~and_langs;  // and_langs already tested - skip
        return test_languages<max_langs>(friendships, know, or_langs, n, r);
    }

    [[nodiscard]] static constexpr int minimumTeachings(
        u16 n,
        std::vector<std::vector<int>>& languages,
        std::vector<std::vector<int>>& friendships) noexcept
    {
        constexpr std::array funcs{
            &Solution::minimumTeachingsT1<64>,
            &Solution::minimumTeachingsT1<64>,
            &Solution::minimumTeachingsT1<64 * 2>,
            &Solution::minimumTeachingsT1<64 * 3>,
            &Solution::minimumTeachingsT1<64 * 4>,
            &Solution::minimumTeachingsT1<64 * 5>,
            &Solution::minimumTeachingsT1<64 * 6>,
            &Solution::minimumTeachingsT1<64 * 7>,
            &Solution::minimumTeachingsT1<64 * 8>,
        };

        return funcs[ceil_div<u16>(n, 64)](n, languages, friendships);
    }
};
