#ifndef __clang__
#pragma GCC optimize("O3")
#endif

#include <algorithm>
#include <cassert>
#include <set>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using ShopID = u32;   // [1; 3 * 10^5]
using MovieID = u16;  // [1; 10^4]
using Price = u16;    // [1; 10^4]

#define FORCE_INLINE inline __attribute__((always_inline))

template <u32 capacity, typename K, typename V, typename Hasher = std::hash<K>>
class HashMap
{
    enum class State : u8
    {
        EMPTY,
        OCCUPIED,
        DELETED
    };

    using KV = std::pair<K, V>;
    using KVStorage = std::array<std::byte, sizeof(KV)>;
    u32 size_{};
    alignas(KV) std::array<KVStorage, capacity> pairs_;
    std::array<State, capacity> states_{};

public:
    HashMap() = default;  // NOLINT

    inline const V* find(const K& key) const noexcept
    {
        u32 idx = probe(key);
        if (idx != capacity && states_[idx] == State::OCCUPIED)
        {
            return &pairs_[idx].second;
        }
        return nullptr;
    }

    inline V* find(const K& key) noexcept
    {
        u32 idx = probe(key);
        if (idx != capacity && states_[idx] == State::OCCUPIED)
        {
            return &at_index(idx).second;
        }
        return nullptr;
    }

    inline V& operator[](const K& key) noexcept
    {
        u32 idx = find_slot(key);
        auto& [k, v] = at_index(idx);
        if (states_[idx] != State::OCCUPIED)
        {
            assert(size_ != capacity);
            ++size_;
            states_[idx] = State::OCCUPIED;
            new (&k) K(key);
            new (&v) V();
        }

        return v;
    }

    inline bool erase(const K& key) noexcept
    {
        u32 idx = probe(key);
        if (idx != capacity && states_[idx] == State::OCCUPIED)
        {
            states_[idx] = State::DELETED;
            --size_;
            return true;
        }
        return false;
    }

    inline void clear() noexcept
    {
        states_.fill(State::EMPTY);
        size_ = 0;
    }

private:
    FORCE_INLINE u32 hash(const K& key) const noexcept
    {
        size_t h = Hasher{}(key);
        // MurmurHash3-style avalanche to mix bits
        h ^= h >> 33;
        h *= 0xff51afd7ed558ccdULL;
        h ^= h >> 33;
        h *= 0xc4ceb9fe1a85ec53ULL;
        h ^= h >> 33;
        return h & (capacity - 1);
    }

    u32 find_slot(const K& key) const noexcept
    {
        u32 idx = hash(key);
        u32 start = idx;
        while (states_[idx] == State::OCCUPIED && at_index(idx).first != key)
        {
            ++idx;
            idx %= capacity;
            assert(idx != start);  // Hash map full ?
        }
        return idx;
    }

    u32 probe(const K& key) const noexcept
    {
        u32 idx = hash(key);
        u32 start = idx;
        while (states_[idx] != State::EMPTY)
        {
            if (states_[idx] == State::OCCUPIED && at_index(idx).first == key)
            {
                return idx;
            }
            ++idx;
            idx %= capacity;
            if (idx == start) break;
        }
        return capacity;
    }

    FORCE_INLINE KV& at_index(u32 index) noexcept
    {
        return reinterpret_cast<KV&>(pairs_[index]);  // NOLINT
    }
    FORCE_INLINE const KV& at_index(u32 index) const noexcept
    {
        return reinterpret_cast<const KV&>(pairs_[index]);  // NOLINT
    }
};

template <size_t num_bytes>
struct GlobalBufferStorage
{
    FORCE_INLINE static GlobalBufferStorage& Instance() noexcept
    {
        static GlobalBufferStorage inst;
        return inst;
    }

    FORCE_INLINE void Reset() noexcept { allocator_offset_ = 0; }

    std::array<std::byte, num_bytes> allocator_memory_;
    size_t allocator_offset_;
};

template <typename T, typename S>
struct BumpAllocator
{
    using value_type = T;

    BumpAllocator() = default;

    template <class U>
    FORCE_INLINE explicit constexpr BumpAllocator(
        const BumpAllocator<U, S>&) noexcept
    {
    }

    [[nodiscard]] FORCE_INLINE T* allocate(std::size_t n) noexcept
    {
        auto& inst = S::Instance();

        // raw buffer start
        std::byte* base = inst.allocator_memory_.data();

        // align current offset for T
        std::size_t alignment = alignof(T);
        std::size_t offset = inst.allocator_offset_;
        std::size_t aligned_offset =
            (offset + (alignment - 1)) & ~(alignment - 1);

        // compute how many bytes we need
        std::size_t bytes = n * sizeof(T);

        assert(aligned_offset + bytes <= inst.allocator_memory_.size());

        // pointer to aligned location
        void* p = base + aligned_offset;  // NOLINT

        // bump offset
        inst.allocator_offset_ = aligned_offset + bytes;

        return static_cast<T*>(p);
    }

    FORCE_INLINE void deallocate(T*, std::size_t) noexcept {}

    // equality so containers can compare allocators
    FORCE_INLINE constexpr bool operator==(const BumpAllocator&) const noexcept
    {
        return true;
    }
    FORCE_INLINE constexpr bool operator!=(const BumpAllocator&) const noexcept
    {
        return false;
    }
};

template <
    typename Element,
    typename AllocatorStorage,
    template <typename> typename Comparator = std::less>
class BumpSet
{
    using Set = std::set<
        Element,
        Comparator<Element>,
        BumpAllocator<Element, AllocatorStorage>>;
    alignas(Set) std::array<std::byte, sizeof(Set)> arr;

public:
    FORCE_INLINE BumpSet() noexcept { new (&get()) Set(); }

    FORCE_INLINE Set& get() noexcept
    {
        return *reinterpret_cast<Set*>(arr.data());  // NOLINT
    }

    FORCE_INLINE const Set& get() const noexcept
    {
        return *reinterpret_cast<const Set*>(arr.data());  // NOLINT
    }

    FORCE_INLINE Set* operator->() noexcept
    {
        return reinterpret_cast<Set*>(arr.data());  // NOLINT
    }

    FORCE_INLINE const Set* operator->() const noexcept
    {
        return reinterpret_cast<const Set*>(arr.data());  // NOLINT
    }
};

using SetStorage = GlobalBufferStorage<1 << 25>;

class MovieRentingSystem
{
private:
    using PairHasher = decltype([](const std::pair<int, int>& p)
        {
        uint64_t v = (u64{std::bit_cast<u32>(p.first)} << 32) |
                     u64{std::bit_cast<u32>(p.second)};
        return std::hash<u64>{}(v);
        });

    inline static HashMap<
        1 << 14,
        MovieID,
        BumpSet<std::pair<Price, ShopID>, SetStorage>>
        unrented;  // NOLINT
    BumpSet<std::tuple<Price, ShopID, MovieID>, SetStorage> rented;
    inline static HashMap<
        1 << 18,
        std::pair<ShopID, MovieID>,
        Price,
        PairHasher>
        prices;  // NOLINT

public:
    MovieRentingSystem(
        [[maybe_unused]] u32 n,
        std::vector<std::vector<int>>& entries) noexcept
    {
        SetStorage::Instance().Reset();
        unrented.clear();
        prices.clear();

        for (auto& entry : entries)
        {
            ShopID shop = static_cast<ShopID>(entry[0]);
            MovieID movie = static_cast<MovieID>(entry[1]);
            Price price = static_cast<Price>(entry[2]);
            unrented[movie]->insert({price, shop});
            prices[{shop, movie}] = price;
        }
    }

    const std::vector<int>& search(MovieID movie) const noexcept
    {
        static std::vector<int> r;
        r.clear();
        if (const auto unrented_it = unrented.find(movie))
        {
            auto it = unrented_it->get().begin();
            auto end = unrented_it->get().end();
            for (size_t i = 0; i != 5 && it != end; ++i, ++it)
            {
                r.push_back(static_cast<int>(it->second));
            }
        }
        return r;
    }

    void rent(ShopID shop, MovieID movie) noexcept
    {
        Price price = prices[{shop, movie}];
        unrented[movie]->erase({price, shop});
        rented->insert({price, shop, movie});
    }

    void drop(ShopID shop, MovieID movie) noexcept
    {
        Price price = prices[{shop, movie}];
        rented->erase({price, shop, movie});
        unrented[movie]->insert({price, shop});
    }

    const std::vector<std::vector<int>>& report() const noexcept
    {
        static auto cache = []()
        {
            std::array<std::vector<std::vector<int>>, 6> r;
            for (size_t i = 0; i != 6; ++i) r[i].resize(i);
            return r;
        }();
        size_t k = std::min<size_t>(5, rented->size());
        auto& r = cache[k];
        auto it = rented->begin();
        for (size_t i = 0; i != k && it != rented->end(); ++i, ++it)
        {
            r[i] = {
                static_cast<int>(get<1>(*it)),
                static_cast<int>(get<2>(*it)),
            };
        }
        return r;
    }
};
