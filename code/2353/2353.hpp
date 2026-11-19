#ifndef __clang__
#pragma GCC optimize("O3")
#endif

#include <cassert>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "integral_aliases.hpp"
#include "no_sanitizers.hpp"
#include "pack_str.hpp"

struct ShiftHasher
{
    [[gnu::always_inline, gnu::hot]] size_t operator()(const uint64_t v) const
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
    [[gnu::always_inline]] inline explicit constexpr BumpAllocator(
        const BumpAllocator<U>&) noexcept
    {
    }

    [[nodiscard, gnu::always_inline, gnu::hot]] inline T* allocate(
        std::size_t n) noexcept;

    [[gnu::always_inline]] inline void deallocate(T*, std::size_t) noexcept {}

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

struct SetCmp
{
    [[nodiscard, gnu::always_inline, gnu::hot]] inline constexpr bool
    operator()(const RatedFood& a, const RatedFood& b) const noexcept
        NO_SANITIZERS
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

    [[gnu::hot]] constexpr void changeRating(
        const std::string& food,
        int newRating) noexcept NO_SANITIZERS
    {
        auto packed_food = packStr(food);
        auto& [rating, cuisine_idx] = food_info_[packed_food];
        auto& cuisine_set = sets_[cuisine_idx];  // NOLINT
        auto node = cuisine_set.extract({packed_food, rating});
        rating = newRating;
        node.value().rating = newRating;
        cuisine_set.insert(std::move(node));
    }

    [[nodiscard, gnu::hot]] constexpr std::string highestRated(
        const std::string& cuisine) noexcept NO_SANITIZERS
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

    [[nodiscard, gnu::always_inline]] inline static FoodRatingsS&
    Instance() noexcept
    {
        static FoodRatingsS instance;
        return instance;
    }
};

template <typename T>
[[nodiscard, gnu::always_inline]] inline T* BumpAllocator<T>::allocate(
    std::size_t n) noexcept NO_SANITIZERS
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
    [[gnu::always_inline, gnu::hot]] inline FoodRatings(
        const std::vector<std::string>& foods,
        const std::vector<std::string>& cuisines,
        const std::vector<int>& ratings) noexcept NO_SANITIZERS
    {
        FoodRatingsS::Instance().Initialize(foods, cuisines, ratings);
    }

    [[gnu::always_inline, gnu::hot]] inline void changeRating(
        const std::string& food,
        int newRating) noexcept NO_SANITIZERS
    {
        FoodRatingsS::Instance().changeRating(food, newRating);
    }

    [[gnu::always_inline, gnu::hot]] inline std::string highestRated(
        const std::string& cuisine) noexcept NO_SANITIZERS
    {
        return FoodRatingsS::Instance().highestRated(cuisine);
    }
};
