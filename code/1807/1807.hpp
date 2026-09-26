#include <algorithm>
#include <array>
#include <bit>
#include <cstring>
#include <string>
#include <vector>

#include "pack_str.hpp"
#include "sync_stdio.hpp"

class Solution
{
public:
    struct Entry
    {
        u64 key;
        u64 value;
    };

    inline static Entry entries[1 << 17];

    template <u32 capacity>
    struct HashTable
    {
        [[gnu::always_inline, gnu::no_sanitize_address]] Entry& slot(
            u64 key) noexcept
        {
            u64 z = key + 0x9e3779b97f4a7c15ULL;
            z = (z ^ (z >> 30U)) * 0xbf58476d1ce4e5b9ULL;
            z = (z ^ (z >> 27U)) * 0x94d049bb133111ebULL;
            u32 i = cast<u32>(z >> 32U) & (capacity - 1);
            while (entries[i].key && entries[i].key != key)
            {
                i = (i + 1) & (capacity - 1);
            }
            return entries[i];
        }
    };

    [[gnu::no_sanitize_address]] static std::string_view
    consume(std::string_view s, size_t& i, char until) noexcept
    {
        size_t begin = i;
        i = s.find(until, i);
        return s.substr(begin, i - begin);
    }

    [[gnu::no_sanitize_address]] static std::string decode(
        auto& m,
        std::string_view key) noexcept
    {
        const auto& entry = m.slot(packStr(std::string{key}));
        if (entry.key)
        {
            return unpackStr(entry.value);
        }
        return "?";
    }

    template <u32 capacity>
    [[gnu::no_sanitize_address]] static std::string impl(
        std::string_view s,
        const std::vector<std::vector<std::string>>& knowledge) noexcept
    {
        std::string r;
        r.reserve((s.size() * 3) / 2);
        HashTable<capacity> m;
        std::memset(entries, 0, capacity * sizeof(Entry));
        for (auto& t : knowledge)
        {
            auto key = packStr(t[0]);
            m.slot(key) = {key, packStr(t[1])};
        }

        size_t i = 0, n = s.size();

        while (i < n)
        {
            r += consume(s, i, '(');
            if (i < n)
            {
                ++i;  // '('
                r += decode(m, consume(s, i, ')'));
                ++i;  // ')'
            }
        }

        return r;
    }

    [[gnu::no_sanitize_address]] std::string evaluate(
        std::string_view s,
        const std::vector<std::vector<std::string>>& knowledge) const noexcept
    {
        constexpr std::array fns{
            impl<1 << 0>,
            impl<1 << 1>,
            impl<1 << 2>,
            impl<1 << 3>,
            impl<1 << 4>,
            impl<1 << 5>,
            impl<1 << 6>,
            impl<1 << 7>,
            impl<1 << 8>,
            impl<1 << 9>,
            impl<1 << 10>,
            impl<1 << 11>,
            impl<1 << 12>,
            impl<1 << 13>,
            impl<1 << 14>,
            impl<1 << 15>,
            impl<1 << 16>,
            impl<1 << 17>,
        };
        const auto index = std::min(
            17,
            std::bit_width(knowledge.size() + knowledge.size() / 2));
        return fns[cast<size_t>(index)](s, knowledge);
    }
};
