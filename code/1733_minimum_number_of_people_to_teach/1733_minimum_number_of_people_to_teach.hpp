#pragma once

#include <bit>
#include <bitset>
#include <vector>

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

        u16 r = languages.size() & 0xFFFF;

        for (u16 lang = 1; lang <= n; ++lang)
        {
            std::bitset<512> learners;
            u16 cnt = 0;
            for (u16 f = 0; f != friendships.size() && cnt < r; ++f)
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

            r = std::min(r, cnt);
        }

        return r;
    }

    [[nodiscard]] static constexpr int minimumTeachings(
        u16 n,
        std::vector<std::vector<int>>& languages,
        std::vector<std::vector<int>>& friendships) noexcept
    {
        switch (std::bit_ceil(static_cast<u16>(n + 1)))
        {
        case 128:
            return minimumTeachingsT1<128>(n, languages, friendships);
            break;
        case 256:
            return minimumTeachingsT1<256>(n, languages, friendships);
            break;
        case 512:
            return minimumTeachingsT1<512>(n, languages, friendships);
            break;
        default:
            return minimumTeachingsT1<64>(n, languages, friendships);
            break;
        }
    }
};
