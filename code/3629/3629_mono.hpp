#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <numeric>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>





#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

#define HOT_PATH __attribute__((hot))


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

    FORCE_INLINE void Reset() const noexcept { *offset = rollback_offset; }

    FORCE_INLINE ~ScopedArena() noexcept
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
    FORCE_INLINE static GlobalBufferStorage& Instance() noexcept
    {
        static GlobalBufferStorage inst;
        return inst;
    }

    FORCE_INLINE void Reset() noexcept { allocator_offset_ = 0; }

    [[nodiscard]] FORCE_INLINE ScopedArena StartArena() noexcept
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
    FORCE_INLINE explicit constexpr BumpAllocator(
        const BumpAllocator<U, S>&) noexcept
    {
    }

    [[nodiscard]] FORCE_INLINE T* allocate(u32 n) noexcept HOT_PATH
        NO_SANITIZERS
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

    FORCE_INLINE void deallocate(T*, u32) noexcept {}

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

template <typename T>
class ObjectWithoutDtor
{
    alignas(T) std::array<std::byte, sizeof(T)> arr;

public:
    FORCE_INLINE ObjectWithoutDtor() noexcept { Reset(); }
    FORCE_INLINE void Reset() noexcept { new (&get()) T(); }

    FORCE_INLINE T& get() noexcept
    {
        return *reinterpret_cast<T*>(arr.data());  // NOLINT
    }

    FORCE_INLINE const T& get() const noexcept
    {
        return *reinterpret_cast<const T*>(arr.data());  // NOLINT
    }

    FORCE_INLINE T* operator->() noexcept
    {
        return reinterpret_cast<T*>(arr.data());  // NOLINT
    }

    FORCE_INLINE const T* operator->() const noexcept
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



template <typename V, typename Storage, typename Cmp = std::less<V>>
using BumpSet = std::set<V, Cmp, BumpAllocator<V, Storage>>;


template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};


template <std::integral T>
[[nodiscard, gnu::always_inline]] static constexpr T ceil_div(
    T a,
    std::type_identity_t<T> b) noexcept
{
    return (a + (b - 1)) / b;
}

struct EmptyType
{
};

inline static constexpr EmptyType kEmpty{};



template <u32 n, u32 primes_capacity>
class Factorizer
{
public:
    std::array<u32, n + 1> spf{};
    std::array<u32, primes_capacity> primes;
    u32 num_primes = 0;

    Factorizer() noexcept  // NOLINT
    {
        for (u32 x = 2u; x <= n; ++x)
        {
            if (spf[x] == 0u)
            {
                spf[x] = x;
                primes[num_primes++] = x;
            }

            for (u32 prime_index = 0; prime_index != num_primes; ++prime_index)
            {
                u32 prime = primes[prime_index];
                const u64 prod64 = u64{prime} * u64{x};
                if (prod64 > n) break;
                u32 prod = cast<u32>(prod64);
                spf[prod] = prime;
                if (prime == spf[x]) break;
            }
        }
    }

    template <typename Callback>
    [[gnu::always_inline]] void factorize(u32 x, Callback callback)
        const noexcept
    {
        while (x > 1)
        {
            u32 prime = spf[x], power = 0u;
            while (!(x % prime))
            {
                x /= prime;
                ++power;
            }
            callback(prime, power);
        }
    }

    [[nodiscard]] constexpr u32 prime_at_index(u32 idx) const noexcept
    {
        return primes[idx];
    }
};



struct FullType
{
};

inline static constexpr FullType kFull{};



template <u64 value>
using UintForValue = std::conditional_t < value < (1 << 8),
      u8,
      std::conditional_t <
          value<
              (1 << 16),
              u16,
              std::conditional_t<value<(1UL << 32), u32, u64>>>;

template <size_t capacity, typename Word = u64>
class PyramidBitset
{
public:
    using ValueType = UintForValue<capacity - 1>;
    static constexpr size_t kWordSize = sizeof(Word) * 8;
    static constexpr u8 kMask = kWordSize - 1;
    static constexpr int kShift = std::bit_width(kMask);
    static constexpr size_t kNumLayers =
        ceil_div(std::bit_width(capacity), kShift);
    static constexpr auto kLayersSizes = []
    {
        std::array<size_t, kNumLayers> sizes{};
        for (size_t i = 0, x = capacity; i != sizes.size(); ++i)
        {
            sizes[i] = x;
            x = ceil_div(x, kWordSize);
        }
        return sizes;
    }();
    static constexpr size_t kTotalWords =
        std::accumulate(kLayersSizes.begin(), kLayersSizes.end(), 0UZ);
    std::array<Word, kTotalWords> words;

    template <u8 i>
    struct LyrIdx
    {
        // NOLINTNEXTLINE
        [[nodiscard]] consteval operator u8() const noexcept { return i; }
    };

    static constexpr auto offsets = []
    {
        std::array<size_t, kNumLayers> offsets;  // NOLINT
        std::exclusive_scan(
            kLayersSizes.begin(),
            kLayersSizes.end(),
            offsets.begin(),
            size_t{});
        return offsets;
    }();

    constexpr PyramidBitset() = default;

    // NOLINTNEXTLINE
    constexpr PyramidBitset(FullType, size_t size = capacity) noexcept
    {
        assert(size <= capacity);
        initialize(kFull, size);
    }

    // NOLINTNEXTLINE
    constexpr PyramidBitset(EmptyType, size_t size = capacity) noexcept
    {
        assert(size <= capacity);
        initialize(kEmpty, size);
    }

    template <bool v>
    [[gnu::always_inline]] constexpr void set(ValueType idx) noexcept
    {
        if constexpr (v)
        {
            add(idx);
        }
        else
        {
            remove(idx);
        }
    }

    [[gnu::always_inline]] constexpr void set(ValueType idx, bool v) noexcept
    {
        if (v)
        {
            add(idx);
        }
        else
        {
            remove(idx);
        }
    }

    [[gnu::always_inline]] constexpr void add(ValueType v) noexcept
    {
        for_each_layer(
            [&] [[gnu::always_inline]] (auto layer) noexcept
            {
                ValueType wi = v >> kShift;
                words[offsets[layer] + wi] |= Word{1} << (v & kMask);
                v = wi;
            });
    }

    // Returns true if element did not exist previously
    [[nodiscard, gnu::always_inline]] constexpr bool add_ex(
        ValueType v) noexcept
    {
        bool added = false;
        for_each_layer(
            [&] [[gnu::always_inline]] (auto layer) noexcept
            {
                ValueType wi = v >> kShift;
                auto& word = words[offsets[layer] + wi];
                Word m = Word{1} << (v & kMask);
                if constexpr (layer == 0)
                {
                    added = (word & m) == 0;
                }
                word |= m;
                v = wi;
            });
        return added;
    }

    [[gnu::always_inline]] constexpr void remove(ValueType v) noexcept
    {
        bool prev_empty = true;
        for_each_layer(
            [&] [[gnu::always_inline]] (auto layer) noexcept
            {
                ValueType wi = v >> kShift;
                auto& w = words[offsets[layer] + wi];
                w &= ~(Word{prev_empty} << (v & kMask));
                v = wi;
                prev_empty = !w;
            });
    }

    [[nodiscard, gnu::always_inline]] constexpr ValueType min() const noexcept
    {
        ValueType wi = 0;
        for_each_layer_reversed(
            [&] [[gnu::always_inline]] (auto layer) noexcept
            {
                u8 bi = std::countr_zero(words[offsets[layer] + wi]) & 0xFF;
                ValueType x =
                    cast<ValueType>(wi << kShift) | cast<ValueType>(bi);
                wi = x;
            });
        return wi;
    }

    [[nodiscard, gnu::always_inline]] constexpr ValueType max() const noexcept
    {
        ValueType wi = 0;
        for_each_layer_reversed(
            [&] [[gnu::always_inline]] (auto layer) noexcept
            {
                u8 bi =
                    kMask - std::countl_zero(words[offsets[layer] + wi]) & 0xFF;
                ValueType x =
                    cast<ValueType>(wi << kShift) | cast<ValueType>(bi);
                wi = x;
            });
        return wi;
    }

    [[nodiscard, gnu::always_inline]] constexpr bool get(
        ValueType v) const noexcept
    {
        return words[offsets[0] + (v >> kShift)] & (Word{1} << (v & kMask));
    }

    [[nodiscard, gnu::always_inline]] static constexpr size_t
    get_capacity() noexcept
    {
        return capacity;
    }

    [[nodiscard, gnu::always_inline]] constexpr bool is_empty() const noexcept
    {
        return words[offsets[kNumLayers - 1]] == 0;
    }

    [[gnu::always_inline]] constexpr void initialize(
        FullType,
        size_t end = capacity) noexcept
    {
        initialize<true>(end);
    }

    [[gnu::always_inline]] constexpr void initialize(
        EmptyType,
        size_t end = capacity) noexcept
    {
        initialize<false>(end);
    }

    template <bool value>
    [[gnu::always_inline]] constexpr void initialize(
        size_t end = capacity) noexcept
    {
        constexpr auto m = value ? ~Word{} : Word{};
        for_each_layer(
            [&] [[gnu::always_inline]] (auto layer) noexcept
            {
                end = ceil_div<size_t>(end, kWordSize);
                std::fill_n(std::next(words.begin(), offsets[layer]), end, m);
            });
    }

private:
    template <typename F>
    [[gnu::always_inline]] constexpr static void for_each_layer(F&& f) noexcept
    {
        [&]<size_t... layer> [[gnu::always_inline]] (
            std::index_sequence<layer...>) noexcept
        {
            (f(LyrIdx<layer>{}), ...);
        }(std::make_index_sequence<kNumLayers>());
    }

    template <typename F>
    [[gnu::always_inline]] constexpr static void for_each_layer_reversed(
        F&& f) noexcept
    {
        for_each_layer([&] [[gnu::always_inline]] (auto layer) noexcept
                       { f(LyrIdx<kNumLayers - (layer + 1)>{}); });
    }
};

inline static const Factorizer<1'000'001, 100'001> factorizer;

using SolutionStorage = GlobalBufferStorage<1 << 25>;

class Solution
{
public:
    static constexpr u32 impl(const std::vector<u32>& nums) noexcept
    {
        auto _ = SolutionStorage::Instance().StartArena();
        const u32 n = cast<u32>(nums.size());

        // next[i] saves the index in the array nums
        // such that nums[i] == nums[next[i]] or '~u32{}' if
        // this is the last element in the list of duplicates
        static u32 next[100'000];
        std::fill_n(next, n, ~u32{});

        // a map from a value to the index i in nums
        // which denotes the first element in the linked
        // list of duplicates
        ObjectWithoutDtor<BumpHashMap<u32, u32, SolutionStorage>> head;
        head->reserve(2 * n);

        for (u32 i = 0; i != n; ++i)
        {
            auto it = head->try_emplace(nums[i], ~u32{}).first;
            next[i] = std::exchange(it->second, i);
        }

        // Key is value in nums
        // value is a set of values in nums
        ObjectWithoutDtor<BumpHashMap<
            u32,
            ObjectWithoutDtor<BumpSet<u32, SolutionStorage>>,
            SolutionStorage>>
            edges;
        for (u32 i = 0; i != n; ++i)
        {
            u32 v = nums[i];

            for (u32 x = v; x > 1;)
            {
                u32 prime = factorizer.spf[x];
                while (!(x % prime)) x /= prime;

                if (head->contains(prime))
                {
                    edges.get()[prime]->insert(v);
                }
            }
        }

        static u64 visited_words[ceil_div(100'000, 64)];
        std::fill_n(visited_words, ceil_div(n, 64), 0);
        PyramidBitset<100'000> a(kEmpty, n), b(kEmpty, n);

        auto front = &a, back = &b;

        auto visited = [] [[gnu::always_inline]] (u32 i)
        {
            auto& w = visited_words[i >> 6];
            return w & (u64{1} << (i & 63));
        };
        auto visit = [] [[gnu::always_inline]] (u32 i)
        {
            auto& w = visited_words[i >> 6];
            w |= (u64{1} << (i & 63));
        };

        u32 queue_size = 1;
        front->add(0);

        for (u32 step = 0;; ++step)
        {
            u32 next_size = 0;
            auto enqueue = [&] [[gnu::always_inline]] (u32 j) noexcept
            {
                next_size += back->add_ex(j & -u32{!visited(j)});
            };

            while (queue_size--)
            {
                u32 i = front->max();
                front->remove(i);

                if (i + 1 == n) return step;
                if (visited(i)) continue;
                visit(i);

                if (i && !visited(i - 1)) enqueue(i - 1);
                enqueue(i + 1);

                u32 v = nums[i];
                auto it = edges->find(v);
                if (it == edges->end()) continue;

                for (auto& vj : it->second.get())
                {
                    auto it2 = head->find(vj);
                    if (it2 == head->end()) continue;
                    for (u32 j = it2->second; j != ~u32{}; j = next[j])
                    {
                        enqueue(j);
                    }
                    head->erase(it2);
                }
            }

            queue_size = next_size;
            std::swap(front, back);
        }

        std::unreachable();
    }

    u32 minJumps(std::vector<int>& nums) noexcept
    {
        return impl(reinterpret_cast<std::vector<u32>&>(nums));
    }
};
