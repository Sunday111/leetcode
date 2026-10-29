#include <array>
#include <bit>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

#define NO_SANITIZERS \
    __attribute__((no_sanitize("undefined", "address", "coverage", "thread")))

struct ScopedArena
{
    u32 rollback_offset = 0;
    u32* offset = nullptr;

    [[gnu::always_inline]] inline void Reset() const noexcept
    {
        *offset = rollback_offset;
    }

    [[gnu::always_inline]] inline ~ScopedArena() noexcept
    {
        if (offset)
        {
            Reset();
            offset = nullptr;
        }
    }
};

template <u32 num_bytes>
struct GlobalBufferStorage
{
    [[gnu::always_inline]] inline static GlobalBufferStorage&
    Instance() noexcept
    {
        static GlobalBufferStorage inst;
        return inst;
    }

    [[gnu::always_inline]] inline void Reset() noexcept
    {
        allocator_offset_ = 0;
    }

    [[nodiscard, gnu::always_inline]] inline ScopedArena StartArena() noexcept
    {
        return {allocator_offset_, &allocator_offset_};
    }

    alignas(64) std::array<std::byte, num_bytes> allocator_memory_;
    u32 allocator_offset_;
};

template <typename T, typename S>
struct BumpAllocator
{
    using value_type = T;

    BumpAllocator() = default;

    template <class U>
    [[gnu::always_inline]] inline explicit constexpr BumpAllocator(
        const BumpAllocator<U, S>&) noexcept
    {
    }

    [[nodiscard, gnu::always_inline, gnu::hot]] inline T* allocate(
        u32 n) noexcept NO_SANITIZERS
    {
        auto& inst = S::Instance();

        // align current offset for T
        u32 alignment = alignof(T);
        u32 offset = inst.allocator_offset_;
        u32 aligned_offset = (offset + (alignment - 1)) & ~(alignment - 1);
        u32 bytes = n * sizeof(T);

        assert(aligned_offset + bytes <= inst.allocator_memory_.size());

        // bump offset
        inst.allocator_offset_ = aligned_offset + bytes;

        return reinterpret_cast<T*>(
            inst.allocator_memory_.data() + aligned_offset);  // NOLINT
    }

    [[gnu::always_inline]] inline void deallocate(T*, u32) noexcept {}

    // equality so containers can compare allocators
    [[gnu::always_inline]] inline constexpr bool operator==(
        const BumpAllocator&) const noexcept
    {
        return true;
    }
    [[gnu::always_inline]] inline constexpr bool operator!=(
        const BumpAllocator&) const noexcept
    {
        return false;
    }
};

template <typename T>
class ObjectWithoutDtor
{
    alignas(T) std::array<std::byte, sizeof(T)> arr;

public:
    [[gnu::always_inline]] inline ObjectWithoutDtor() noexcept { Reset(); }
    [[gnu::always_inline]] inline void Reset() noexcept { new (&get()) T(); }

    [[gnu::always_inline]] inline T& get() noexcept
    {
        return *reinterpret_cast<T*>(arr.data());  // NOLINT
    }

    [[gnu::always_inline]] inline const T& get() const noexcept
    {
        return *reinterpret_cast<const T*>(arr.data());  // NOLINT
    }

    [[gnu::always_inline]] inline T* operator->() noexcept
    {
        return reinterpret_cast<T*>(arr.data());  // NOLINT
    }

    [[gnu::always_inline]] inline const T* operator->() const noexcept
    {
        return reinterpret_cast<const T*>(arr.data());  // NOLINT
    }
};

template <
    typename Key,
    typename Value,
    typename Storage,
    typename Hash = std::hash<Key>,
    typename Cmp = std::equal_to<Key>>
using BumpHashMap = std::unordered_map<
    Key,
    Value,
    Hash,
    Cmp,
    BumpAllocator<std::pair<const Key, Value>, Storage>>;
#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

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
