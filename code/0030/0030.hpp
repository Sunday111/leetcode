#include <bit>
#include <cstring>
#include <string>
#include <string_view>
#include <vector>

#include "bump_allocator.hpp"
#include "bump_hash_map.hpp"
#include "integral_aliases.hpp"
#include "sync_stdio.hpp"

class Solution
{
public:
    using SolutionStorage = GlobalBufferStorage<1 << 19>;
    struct WordCounts
    {
        u16 required = 0;
        u16 current = 0;
        u16 generation = 0;
    };

    struct WordTable
    {
        struct Entry
        {
            u64 key{};
            WordCounts counts{};
        };
        Entry* entries;
        u32 mask;

        explicit WordTable(u32 num_words)
        {
            const u32 capacity = std::bit_ceil(2 * num_words);
            entries =
                BumpAllocator<Entry, SolutionStorage>{}.allocate(capacity);
            std::memset(entries, 0, capacity * sizeof(Entry));
            mask = capacity - 1;
        }

        WordCounts* get(u64 key, bool insert = false)
        {
            u64 hash = key + 0x9e3779b97f4a7c15ULL;
            hash = (hash ^ (hash >> 30U)) * 0xbf58476d1ce4e5b9ULL;
            hash = (hash ^ (hash >> 27U)) * 0x94d049bb133111ebULL;
            hash ^= hash >> 31U;
            u32 i = hash & mask;
            while (entries[i].key != 0 && entries[i].key != key)
            {
                i = (i + 1) & mask;
            }
            auto& entry = entries[i];
            if (entry.key == 0)
            {
                if (!insert) return nullptr;
                entry.key = key;
            }
            return &entry.counts;
        }
    };

    static u64 pack(std::string_view word)
    {
        u64 key = 0;
        for (char c : word) key = (key << 5) | (c & 31);
        return key;
    }

    static std::vector<int>
    scan(std::string_view s, u32 num_words, u32 word_len, const auto& find)
    {
        const u32 total_len = num_words * word_len;
        auto* window =
            BumpAllocator<WordCounts*, SolutionStorage>{}.allocate(num_words);

        const u32 l = s.size() & ~0u;
        std::vector<int> ans;
        ans.reserve(s.size() - total_len + 1);
        u16 generation = 0;
        for (u32 offset = 0; offset != word_len; ++offset)
        {
            ++generation;
            u32 left = offset;
            u32 head = 0;
            u32 tail = 0;
            for (u32 right = offset; right + word_len <= l; right += word_len)
            {
                auto* entry = find(s.substr(right, word_len));
                if (!entry)
                {
                    ++generation;
                    head = tail = 0;
                    left = right + word_len;
                    continue;
                }

                auto& counts = *entry;
                if (counts.generation != generation)
                {
                    counts.current = 0;
                    counts.generation = generation;
                }
                ++counts.current;
                while (counts.current > counts.required)
                {
                    --window[head]->current;
                    if (++head == num_words) head = 0;
                    left += word_len;
                }

                window[tail] = &counts;
                if (++tail == num_words) tail = 0;

                if (right + word_len - left == total_len)
                {
                    ans.push_back(static_cast<int>(left));
                }
            }
        }
        return ans;
    }

    template <u32 word_len>
    static std::vector<int> solve_direct(
        std::string_view s,
        const std::vector<std::string>& words)
    {
        constexpr u32 capacity = word_len == 1 ? 26 : 26 * 26;
        auto* counts =
            BumpAllocator<WordCounts, SolutionStorage>{}.allocate(capacity);
        std::memset(counts, 0, capacity * sizeof(WordCounts));
        auto index = [](std::string_view word)
        {
            auto key = word[0] - 'a';
            if constexpr (word_len == 2) key = key * 26 + word[1] - 'a';
            return key;
        };
        for (const auto& word : words) ++counts[index(word)].required;
        return scan(
            s,
            words.size() & ~0u,
            word_len,
            [&](std::string_view word)
            {
                auto* entry = counts + index(word);
                return entry->required ? entry : nullptr;
            });
    }

    std::vector<int> findSubstring(
        std::string_view s,
        std::vector<std::string>& words)
    {
        const u32 word_len = words.front().size() & ~0u;
        const u32 num_words = words.size() & ~0u;
        if (num_words * word_len > s.size()) return {};
        auto arena = SolutionStorage::Instance().StartArena();
        if (word_len == 1) return solve_direct<1>(s, words);
        if (word_len == 2) return solve_direct<2>(s, words);
        if (word_len <= 12)
        {
            WordTable table(num_words);
            for (const auto& word : words)
            {
                ++table.get(pack(word), true)->required;
            }
            return scan(
                s,
                num_words,
                word_len,
                [&](std::string_view word) { return table.get(pack(word)); });
        }
        ObjectWithoutDtor<
            BumpHashMap<std::string_view, WordCounts, SolutionStorage>>
            table;
        table->reserve(num_words);
        for (const auto& word : words) ++table.get()[word].required;
        return scan(
            s,
            num_words,
            word_len,
            [&](std::string_view word)
            {
                auto it = table->find(word);
                return it == table->end() ? nullptr : &it->second;
            });
    }
};
