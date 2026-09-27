#include <immintrin.h>

#include <algorithm>
#include <array>
#include <bit>
#include <cstring>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include "cast.hpp"
#include "integral_aliases.hpp"
#include "sync_stdio.hpp"

struct HashTableStorage
{
    struct Entry
    {
        u64 key;
        u64 value;
    };

    inline static Entry entries[1 << 17];
    inline static Entry missing{};
    inline static u64 bits[(1 << 17) / 64];

    [[gnu::always_inline, gnu::no_sanitize_address]] static u32 hash(
        u64 key) noexcept
    {
        u64 z = key + 0x9e3779b97f4a7c15ULL;
        z = (z ^ (z >> 30U)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27U)) * 0x94d049bb133111ebULL;
        return cast<u32>(z >> 32U);
    }

    [[gnu::always_inline, gnu::no_sanitize_address]] static u64 lookup(
        u64 key,
        u32 mask) noexcept
    {
        // Query-built tables already contain every key the renderer can
        // request.
        u32 i = hash(key) & mask;
        while (entries[i].key && entries[i].key != key) i = (i + 1) & mask;
        return entries[i].value;
    }
};

template <u32 capacity, bool use_bits>
struct HashTable : HashTableStorage
{
    [[gnu::always_inline, gnu::no_sanitize_address]] HashTable() noexcept
    {
        if constexpr (use_bits)
        {
            std::memset(bits, 0, std::max(1u, capacity / 64) * sizeof(u64));
        }
        else
        {
            std::memset(entries, 0, capacity * sizeof(Entry));
        }
    }

    [[gnu::always_inline, gnu::no_sanitize_address]] Entry& slot(
        u64 key,
        bool insert = false) noexcept
    {
        u32 i = hash(key) & (capacity - 1);
        if constexpr (use_bits)
        {
            while ((bits[i >> 6] & (u64{1} << (i & 63))) &&
                   entries[i].key != key)
            {
                i = (i + 1) & (capacity - 1);
            }
            auto& word = bits[i >> 6];
            const auto mask = u64{1} << (i & 63);
            if (!(word & mask))
            {
                if (!insert)
                {
                    return missing;
                }
                entries[i] = {key, 0};
                word |= mask;
            }
        }
        else
        {
            while (entries[i].key && entries[i].key != key)
            {
                i = (i + 1) & (capacity - 1);
            }
        }
        return entries[i];
    }
};

class Solution
{
public:
    // Five low bits per lowercase letter; zero padding terminates the value.
    template <size_t n>
    [[gnu::always_inline, gnu::target("bmi2")]] static u64 packFixed(
        const char* p) noexcept
    {
        if constexpr (n == 0)
        {
            return 0;
        }
        else if constexpr (n == 1)
        {
            return cast<u64>(*p & 31);
        }
        else
        {
            constexpr size_t width = std::bit_floor(n);
            using Word = std::conditional_t<
                width == 8,
                u64,
                std::conditional_t<width == 4, u32, u16>>;
            Word word{};
            std::memcpy(&word, p, width);
            const u64 packed = width == 8
                                   ? _pext_u64(word, 0x1f1f1f1f1f1f1f1fULL)
                                   : _pext_u32(word, cast<Word>(0x1f1f1f1fU));
            return packed | (packFixed<n - width>(p + width) << (5 * width));
        }
    }
    [[gnu::hot, gnu::target("bmi2"), gnu::no_sanitize_address]]
    static u64 packStr10(const auto& s) noexcept
    {
        const auto n = s.size();
        const auto* p = s.data();
        switch (n)
        {
        case 0:
            return 0;
        case 1:
            return packFixed<1>(p);
        case 2:
            return packFixed<2>(p);
        case 3:
            return packFixed<3>(p);
        case 4:
            return packFixed<4>(p);
        case 5:
            return packFixed<5>(p);
        case 6:
            return packFixed<6>(p);
        case 7:
            return packFixed<7>(p);
        case 8:
            return packFixed<8>(p);
        case 9:
            return packFixed<9>(p);
        case 10:
            return packFixed<10>(p);
        default:
            __builtin_unreachable();
        }
    }

    // Max length before more than capacity/2 distinct keys can fit;
    // shortest keys first: 26 cost 3, 676 cost 4, 17576 cost 5, then cost 6.
    inline static constexpr std::array<size_t, 17> query_lengths{
        2,
        5,
        8,
        14,
        26,
        50,
        105,
        233,
        489,
        1001,
        2025,
        4396,
        9516,
        19756,
        40236,
        81196,
        100000};
    // For length bucket [2^(i-1), 2^i-1], max output is 10*(L/3)+L%3,
    // since a three-character placeholder can expand to ten characters;
    // L <= 100000.
    inline static constexpr std::array<size_t, 18> output_reserves{
        0,
        1,
        10,
        21,
        50,
        101,
        210,
        421,
        850,
        1701,
        3410,
        6821,
        13650,
        27301,
        54610,
        109221,
        218450,
        333331};

    [[gnu::no_sanitize_address]] static std::string_view
    consume(std::string_view s, size_t& i, char until) noexcept
    {
        size_t begin = i;
        i = s.find(until, i);
        return s.substr(begin, i - begin);
    }

    [[gnu::hot, gnu::target("bmi2"), gnu::no_sanitize_address]]
    static void append(std::string& out, u64 value) noexcept
    {
        if (!value)
        {
            out += '?';
            return;
        }
        const u64 lo =
            _pdep_u64(value, 0x1f1f1f1f1f1f1f1fULL) | 0x6060606060606060ULL;
        const u16 hi = cast<u16>(_pdep_u64(value >> 40, 0x1f1fULL) | 0x6060);
        char chars[10]{};
        std::memcpy(chars, &lo, sizeof(lo));
        std::memcpy(chars + 8, &hi, sizeof(hi));
        out.append(chars, cast<size_t>((std::bit_width(value) + 4) / 5));
    }

    template <u32 capacity, bool query_map>
    [[gnu::no_sanitize_address]] static u32 build(
        std::string_view s,
        const std::vector<std::vector<std::string>>& knowledge) noexcept
    {
        HashTable<capacity, query_map> m;
        if constexpr (query_map)
        {
            for (size_t i = 0; i != s.npos; i = s.find('(', i + 1))
            {
                m.slot(packStr10(consume(s, ++i, ')')), true);
            }
        }

        for (auto& t : knowledge)
        {
            auto key = packStr10(t[0]);
            auto& entry = m.slot(key, !query_map);
            if constexpr (query_map)
            {
                if (entry.key) entry.value = packStr10(t[1]);
            }
            else
            {
                entry = {key, packStr10(t[1])};
            }
        }

        return capacity - 1;
    }

    template <bool query_map>
    [[gnu::no_sanitize_address]] static u32 dispatch(
        std::string_view s,
        const std::vector<std::vector<std::string>>& knowledge,
        size_t count) noexcept
    {
        constexpr auto fns = []<size_t... i>(std::index_sequence<i...>)
        {
            return std::array{build<1 << i, query_map>...};
        }(std::make_index_sequence<query_map ? query_lengths.size() : 18>{});
        size_t index{};
        if constexpr (query_map)
        {
            index = cast<size_t>(
                std::ranges::lower_bound(query_lengths, count) -
                query_lengths.begin());
        }
        else
        {
            index =
                cast<size_t>(std::min(17, std::bit_width(count + count / 2)));
        }
        return fns[index](s, knowledge);
    }

    [[gnu::no_sanitize_address]] std::string evaluate(
        std::string_view s,
        const std::vector<std::vector<std::string>>& knowledge) const noexcept
    {
        const size_t first = s.find('(');
        if (first == std::string_view::npos) return std::string{s};
        const size_t last = cast<size_t>(
            cast<const char*>(::memrchr(s.data(), ')', s.size())) - s.data());
        const size_t length = last - first + 1;
        const auto prefix = s.substr(0, first);
        const auto suffix = s.substr(last + 1);
        s = s.substr(first, length);
        const u32 mask = knowledge.size() < length
                             ? dispatch<false>(s, knowledge, knowledge.size())
                             : dispatch<true>(s, knowledge, length);

        std::string r;
        r.reserve(
            prefix.size() + suffix.size() +
            output_reserves[cast<size_t>(std::bit_width(length))]);
        if (!prefix.empty()) r += prefix;
        size_t i = 0, n = s.size();

        while (i < n)
        {
            r += consume(s, i, '(');
            if (i < n)
            {
                ++i;  // '('
                append(
                    r,
                    HashTableStorage::lookup(
                        packStr10(consume(s, i, ')')),
                        mask));
                ++i;  // ')'
            }
        }

        r += suffix;
        return r;
    }
};
