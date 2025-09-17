#include <immintrin.h>

#include <cassert>
#include <cstdint>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef __clang__
#pragma GCC optimize("O3")
#endif

#ifdef __GNUC__
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#define FORCE_INLINE inline
#endif

#ifdef __GNUC__
#define HOT_PATH __attribute__((hot))
#else
#define FORCE_INLINE inline
#endif

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

#define NO_SANITIZERS \
    __attribute__((no_sanitize("undefined", "address", "coverage", "thread")))

// NOLINTBEGIN
static constexpr u64 BIAS = 0x6060606060606060ull, EXT = 0x1F1F1F1F1F1F1F1Full;
inline u64 packStr(const std::string& s) noexcept
    __attribute__((hot, __target__("bmi2")))
{
    const char* c8 = s.c_str();
    u8 n8 = s.length() & 0xFF;
    u8 sh = 50;
    u64 r = 0;
    if (n8 >= 8)
    {
        const u64 qw = *reinterpret_cast<const u64*>(c8) - BIAS;
        sh -= 40;
        r += _pext_u64(__builtin_bswap64(qw), EXT) << sh;
        c8 += 8;
        n8 -= 8;
    }
    if (n8 >= 4)
    {
        const u32 dw = *reinterpret_cast<const u32*>(c8) - (BIAS & 0xFFFFFFFFu);
        sh -= 20;
        r += u64{_pext_u32(__builtin_bswap32(dw), EXT & 0xFFFFFFFFu)} << sh;
        c8 += 4;
        n8 -= 4;
    }
    if (n8 >= 2)
    {
        const u16 w = *reinterpret_cast<const u16*>(c8) - (BIAS & 0xFFFFu);
        sh -= 10;
        r += u64{_pext_u32(__builtin_bswap32(w) >> 16, EXT & 0xFFFFu)} << sh;
        c8 += 2;
        n8 -= 2;
    }
    if (n8)
    {
        sh -= 5;
        r += (static_cast<u64>(*c8) - (BIAS & 0xFFu)) << sh;
        c8 += 1;
        n8 -= 1;
    }
    return r;
}

inline std::string unpackStr(const u64 v) noexcept
    __attribute__((hot, __target__("bmi2")))
{
    std::string r(10, '\0');
    char* c8 = r.data();
    *reinterpret_cast<u64*>(c8) =
        __builtin_bswap64(_pdep_u64(v >> 10, EXT)) + BIAS;
    *reinterpret_cast<u16*>(c8 + 8u) =
        __builtin_bswap32(
            static_cast<u32>(
                _pdep_u32(static_cast<u32>(v), EXT & 0xFFFFu) +
                (BIAS & 0xFFFFu))
            << 16) &
        0xFFFF;
    const auto end = r.find(BIAS & 0xFFu);
    if (end != std::string::npos) r.resize(end);
    return r;
}
// NOLINTEND

struct ShiftHasher
{
    size_t operator()(const uint64_t v) const
        __attribute__((always_inline, hot))
    {
        return v ^ (v >> 17) ^ (v >> 43);
    }
};

struct RatedFood
{
    u64 name;
    int rating;
};

template <typename T>
struct BumpAllocator
{
    using value_type = T;

    BumpAllocator() noexcept = default;

    template <class U>
    FORCE_INLINE explicit constexpr BumpAllocator(
        const BumpAllocator<U>&) noexcept
    {
    }

    [[nodiscard]] FORCE_INLINE T* allocate(std::size_t n) noexcept HOT_PATH;

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

struct SetCmp
{
    [[nodiscard]] FORCE_INLINE constexpr bool operator()(
        const RatedFood& a,
        const RatedFood& b) const noexcept NO_SANITIZERS HOT_PATH
    {
        if (a.rating != b.rating) return a.rating < b.rating;
        return a.name > b.name;
    }
};

class FoodRatingsS  // NOLINT
{
public:
    constexpr void Initialize(
        const std::vector<std::string>& foods,
        const std::vector<std::string>& cuisines,
        const std::vector<int>& ratings) noexcept NO_SANITIZERS
    {
        allocator_offset_ = 0;

        sets_ = reinterpret_cast<FoodsSet*>(sets_array_data_.data());  // NOLINT

        food_info_.clear();
        cuisine_to_idx_.clear();

        for (u16 food_index = 0; food_index != foods.size(); ++food_index)
        {
            auto food = packStr(foods[food_index]);
            auto cuisine = packStr(cuisines[food_index]);
            auto rating = ratings[food_index];

            auto [it, emplaced] =
                cuisine_to_idx_.try_emplace(cuisine, cuisine_to_idx_.size());

            u16 cuisine_idx = it->second;
            if (emplaced) new (&sets_[cuisine_idx]) FoodsSet();  // NOLINT

            sets_[cuisine_idx].emplace(food, rating);  // NOLINT
            food_info_.emplace(food, std::pair{rating, cuisine_idx});
        }
    }

    constexpr void changeRating(const std::string& food, int newRating) noexcept
        HOT_PATH NO_SANITIZERS
    {
        auto packed_food = packStr(food);
        auto& [rating, cuisine_idx] = food_info_[packed_food];
        auto& cuisine_set = sets_[cuisine_idx];  // NOLINT
        auto node = cuisine_set.extract({packed_food, rating});
        rating = newRating;
        node.value().rating = newRating;
        cuisine_set.insert(std::move(node));
    }

    [[nodiscard]] constexpr std::string highestRated(
        const std::string& cuisine) noexcept HOT_PATH NO_SANITIZERS
    {
        auto& set = sets_[cuisine_to_idx_[packStr(cuisine)]];  // NOLINT
        return unpackStr(set.rbegin()->name);
    }

    std::unordered_map<u64, std::pair<int, u16>, ShiftHasher> food_info_;
    std::unordered_map<u64, u16, ShiftHasher> cuisine_to_idx_;

    using FoodsSet = std::set<RatedFood, SetCmp, BumpAllocator<RatedFood>>;
    using SetsArray = std::array<FoodsSet, 20'002>;
    alignas(
        SetsArray) std::array<std::byte, sizeof(SetsArray)> sets_array_data_;
    FoodsSet* sets_{};

    size_t allocator_offset_ = 0;
    std::array<std::byte, 10'000'000> allocator_memory_;

    [[nodiscard]] FORCE_INLINE static FoodRatingsS& Instance() noexcept
    {
        static FoodRatingsS instance;
        return instance;
    }
};

template <typename T>
[[nodiscard]] FORCE_INLINE T* BumpAllocator<T>::allocate(std::size_t n) noexcept
    NO_SANITIZERS
{
    auto& inst = FoodRatingsS::Instance();

    // raw buffer start
    std::byte* base = inst.allocator_memory_.data();

    // align current offset for T
    std::size_t alignment = alignof(T);
    std::size_t offset = inst.allocator_offset_;
    std::size_t aligned_offset = (offset + (alignment - 1)) & ~(alignment - 1);

    // compute how many bytes we need
    std::size_t bytes = n * sizeof(T);

    assert(aligned_offset + bytes <= inst.allocator_memory_.size());

    // pointer to aligned location
    void* p = base + aligned_offset;  // NOLINT

    // bump offset
    inst.allocator_offset_ = aligned_offset + bytes;

    return static_cast<T*>(p);
}

class FoodRatings
{
public:
    FORCE_INLINE FoodRatings(
        const std::vector<std::string>& foods,
        const std::vector<std::string>& cuisines,
        const std::vector<int>& ratings) noexcept HOT_PATH NO_SANITIZERS
    {
        FoodRatingsS::Instance().Initialize(foods, cuisines, ratings);
    }

    FORCE_INLINE void changeRating(
        const std::string& food,
        int newRating) noexcept HOT_PATH NO_SANITIZERS
    {
        FoodRatingsS::Instance().changeRating(food, newRating);
    }

    FORCE_INLINE std::string highestRated(
        const std::string& cuisine) noexcept HOT_PATH NO_SANITIZERS
    {
        return FoodRatingsS::Instance().highestRated(cuisine);
    }
};
