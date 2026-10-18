#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <utility>
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

template <typename B, typename F>
[[gnu::always_inline]] constexpr void pbs_for_each_layer(F&& f) noexcept
{
    [&]<size_t... layer> [[gnu::always_inline]] (
        std::index_sequence<layer...>) noexcept
    {
        (f(std::integral_constant<size_t, layer>{}), ...);
    }(std::make_index_sequence<B::kNumLayers>());
}

template <typename B, typename F>
[[gnu::always_inline]] constexpr void pbs_for_each_layer_reversed(
    F&& f) noexcept
{
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        { f(std::integral_constant<size_t, B::kNumLayers - (layer + 1)>{}); });
}

template <u64 value>
using UintForValue = std::conditional_t < value < (1 << 8),
      u8,
      std::conditional_t <
          value<
              (1 << 16),
              u16,
              std::conditional_t<value<(1UL << 32), u32, u64>>>;

template <size_t capacity, typename Word = u64>
struct PyramidBitset
{
    static constexpr size_t kCapacity = capacity;
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
            x = ceil_div(x, kWordSize);
            sizes[i] = x;
        }
        return sizes;
    }();
    static constexpr size_t kTotalWords =
        std::accumulate(kLayersSizes.begin(), kLayersSizes.end(), 0UZ);
    std::array<Word, kTotalWords> words;

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
};

template <size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_add(
    PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            typename B::ValueType wi = v >> B::kShift;
            bits.words[B::offsets[layer] + wi] |= Word{1} << (v & B::kMask);
            v = wi;
        });
}

template <size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_add_if(
    PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v,
    bool c) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            typename B::ValueType wi = v >> B::kShift;
            bits.words[B::offsets[layer] + wi] |= Word{c} << (v & B::kMask);
            v = wi;
        });
}

template <size_t capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr bool pbs_add_ex(
    PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    bool added = false;
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            typename B::ValueType wi = v >> B::kShift;
            auto& word = bits.words[B::offsets[layer] + wi];
            Word m = Word{1} << (v & B::kMask);
            if constexpr (layer == 0)
            {
                added = (word & m) == 0;
            }
            word |= m;
            v = wi;
        });
    return added;
}

struct FullType
{
};

inline static constexpr FullType kFull{};

template <bool value, size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    PyramidBitset<capacity, Word>& bits,
    size_t end = capacity) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    constexpr auto m = value ? ~Word{} : Word{};
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            end = ceil_div<size_t>(end, B::kWordSize);
            std::fill_n(
                std::next(bits.words.begin(), B::offsets[layer]),
                end,
                m);
        });
}

template <size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    PyramidBitset<capacity, Word>& bits,
    FullType,
    size_t end = capacity) noexcept
{
    pbs_initialize<true>(bits, end);
}

template <size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_initialize(
    PyramidBitset<capacity, Word>& bits,
    EmptyType,
    size_t end = capacity) noexcept
{
    pbs_initialize<false>(bits, end);
}

template <size_t capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr
    typename PyramidBitset<capacity, Word>::ValueType
    pbs_max(const PyramidBitset<capacity, Word>& bits) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    typename B::ValueType wi = 0;
    pbs_for_each_layer_reversed<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            u8 bi = B::kMask -
                        std::countl_zero(bits.words[B::offsets[layer] + wi]) &
                    0xFF;
            typename B::ValueType x =
                cast<typename B::ValueType>(wi << B::kShift) |
                cast<typename B::ValueType>(bi);
            wi = x;
        });
    return wi;
}

template <size_t capacity, typename Word>
[[gnu::always_inline]] constexpr void pbs_remove(
    PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    bool prev_empty = true;
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            typename B::ValueType wi = v >> B::kShift;
            auto& w = bits.words[B::offsets[layer] + wi];
            w &= ~(Word{prev_empty} << (v & B::kMask));
            v = wi;
            prev_empty = !w;
        });
}

template <size_t capacity, typename Word>
[[nodiscard, gnu::always_inline]] constexpr bool pbs_remove_ex(
    PyramidBitset<capacity, Word>& bits,
    typename PyramidBitset<capacity, Word>::ValueType v) noexcept
{
    using B = PyramidBitset<capacity, Word>;
    bool prev_empty = true, removed = false;
    pbs_for_each_layer<B>(
        [&] [[gnu::always_inline]] (auto layer) noexcept
        {
            typename B::ValueType wi = v >> B::kShift;
            auto& w = bits.words[B::offsets[layer] + wi];
            if constexpr (layer == 0)
            {
                removed = (w & (Word{1} << (v & B::kMask)));
            }

            w &= ~(Word{prev_empty} << (v & B::kMask));
            v = wi;
            prev_empty = !w;
        });

    return removed;
}

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
        PyramidBitset<100'000> a, b;
        pbs_initialize(a, kEmpty, n);
        pbs_initialize(b, kEmpty, n);

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
        pbs_add(*front, 0);

        for (u32 step = 0;; ++step)
        {
            u32 next_size = 0;
            auto enqueue = [&] [[gnu::always_inline]] (u32 j) noexcept
            {
                next_size += pbs_add_ex(*back, j & -u32{!visited(j)});
            };

            while (queue_size--)
            {
                u32 i = pbs_max(*front);
                pbs_remove(*front, i);

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
