#include <algorithm>
#include <bitset>
#include <concepts>
#include <cstdint>
#include <span>
#include <utility>
#include <vector>

#ifdef __GNUC__
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#define FORCE_INLINE inline
#endif

template <std::integral T>
[[nodiscard]] FORCE_INLINE static constexpr T ceil_div(T a, T b) noexcept
{
    return ((a + b) - 1) / b;
}

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

// Returns new end
template <typename ForwardIt, typename UnaryPredicate>
[[nodiscard]] FORCE_INLINE static constexpr ForwardIt
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

// Returns new end. Range overload
template <typename Range, typename UnaryPredicate>
[[nodiscard]] FORCE_INLINE static constexpr auto unstable_remove_if(
    Range& range,
    UnaryPredicate&& p) noexcept
{
    return unstable_remove_if(
        std::begin(range),
        std::end(range),
        std::forward<UnaryPredicate>(p));
}

class Solution
{
public:
    template <u16 max_langs, u16 max_users>
    [[nodiscard]] FORCE_INLINE static constexpr u16 test_languages(
        std::span<const std::pair<u16, u16>> friends,
        std::array<std::bitset<max_langs>, max_users>& know,
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
                std::bitset<max_users> learners;
                for (u16 f = 0; f != friends.size() && cnt < max_r; ++f)
                {
                    u16 a = friends[f].first;
                    u16 b = friends[f].second;
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

    template <u16 max_langs, u16 max_users>
    [[nodiscard]] static constexpr u16 minimumTeachingsT2(
        u16 n,
        const std::vector<std::vector<int>>& languages,
        std::span<std::pair<u16, u16>> friends) noexcept
    {
        const u16 num_users = languages.size() & 0xFFFF;

        // For each used fill a bitset with available languages
        std::array<std::bitset<max_langs>, max_users> know{};
        for (u16 user = 0; user != num_users; ++user)
        {
            auto& user_langs = know[user];
            for (int lang : languages[user])
            {
                user_langs[lang & 0xFFFF] = true;
            }
        }

        // Filter out pairs that are already able to communicate
        friends = {
            friends.begin(),
            unstable_remove_if(
                friends,
                [&](std::pair<u16, u16> fr)
                { return (know[fr.first] & know[fr.second]).count(); })};

        // Nothing to do
        if (friends.empty()) return 0;

        // or_langs - the bitset of all languges some user may need to learn
        auto or_langs = know[friends[0].first] ^ know[friends[0].second];

        // and_langs - contains languages that ALL pairs if applied
        auto and_langs = or_langs;

        for (u16 f = 1; f != friends.size(); ++f)
        {
            auto tmp = know[friends[f].first] ^ know[friends[f].second];
            and_langs &= tmp;
            or_langs |= tmp;
        }

        constexpr auto tst = test_languages<max_langs, max_users>;

        u16 r = tst(friends, know, and_langs, n, num_users);
        or_langs &= ~and_langs;  // and_langs already tested - skip
        return tst(friends, know, or_langs, n, r);
    }

    template <u16 max_langs>
    [[nodiscard]] static constexpr u16 minimumTeachingsT1(
        u16 n,
        const std::vector<std::vector<int>>& languages,
        std::span<std::pair<u16, u16>> friends) noexcept
    {
        constexpr std::array funcs{
            &Solution::minimumTeachingsT2<max_langs, 64>,
            &Solution::minimumTeachingsT2<max_langs, 64>,
            &Solution::minimumTeachingsT2<max_langs, 64 * 2>,
            &Solution::minimumTeachingsT2<max_langs, 64 * 3>,
            &Solution::minimumTeachingsT2<max_langs, 64 * 4>,
            &Solution::minimumTeachingsT2<max_langs, 64 * 5>,
            &Solution::minimumTeachingsT2<max_langs, 64 * 6>,
            &Solution::minimumTeachingsT2<max_langs, 64 * 7>,
            &Solution::minimumTeachingsT2<max_langs, 64 * 8>,
        };

        return funcs[ceil_div<u16>(languages.size() & 0xFFFF, 64)](
            n,
            languages,
            friends);
    }

    [[nodiscard]] static constexpr int minimumTeachings(
        u16 n,
        const std::vector<std::vector<int>>& languages,
        const std::vector<std::vector<int>>& friendships) noexcept
    {
        std::array<std::pair<u16, u16>, 512> friends;
        u16 num_pairs = friendships.size() & 0xFFFF;
        for (u16 i = 0; i != num_pairs; ++i)
        {
            auto& fr = friendships[i];
            friends[i] = {fr[0] - 1, fr[1] - 1};
        }

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

        return funcs[ceil_div<u16>(n, 64)](
            n,
            languages,
            std::span{friends}.first(num_pairs));
    }
};
