#ifndef __clang__
#pragma GCC optimize("O3")
#endif

#include <cassert>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#define NO_SANITIZERS \
    __attribute__((no_sanitize("undefined", "address", "coverage", "thread")))
#define HOT_PATH __attribute__((hot))

#define FORCE_INLINE inline __attribute__((always_inline))
using u16 = uint16_t;

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
        const u16& a,
        const u16& b) const noexcept HOT_PATH;
};

class FoodRatingsS  // NOLINT
{
public:
    constexpr void Initialize(
        std::vector<std::string>& foods,
        std::vector<std::string>& cuisines,
        std::vector<int>& ratings) noexcept NO_SANITIZERS
    {
        allocator_offset_ = 0;
        foods_ = std::move(foods);
        cuisines_ = std::move(cuisines);
        ratings_ = std::move(ratings);

        food_to_idx_.clear();
        cuisine_to_idx_.clear();

        for (u16 food_index = 0; food_index != foods_.size(); ++food_index)
        {
            auto emplace_result = cuisine_to_idx_.try_emplace(
                cuisines_[food_index],
                static_cast<u16>(cuisine_to_idx_.size()));

            u16 cuisine_idx = emplace_result.first->second;

            if (emplace_result.second) sets_[cuisine_idx].clear();

            sets_[cuisine_idx].emplace(food_index);
            food_to_idx_.emplace(
                foods_[food_index],
                std::pair{food_index, cuisine_idx});
        }
    }

    constexpr void changeRating(std::string_view food, int newRating) noexcept
        HOT_PATH NO_SANITIZERS
    {
        auto [food_idx, cuisine_idx] = food_to_idx_[food];
        auto node = sets_[cuisine_idx].extract(food_idx);
        ratings_[food_idx] = newRating;
        sets_[cuisine_idx].insert(std::move(node));
    }

    [[nodiscard]] constexpr const std::string& highestRated(
        std::string_view cuisine) noexcept HOT_PATH NO_SANITIZERS
    {
        u16 cuisine_idx = cuisine_to_idx_[cuisine];
        u16 food_idx = *sets_[cuisine_idx].rbegin();
        return foods_[food_idx];
    }

    std::vector<std::string> foods_;
    std::unordered_map<std::string_view, std::pair<u16, u16>> food_to_idx_;

    std::vector<std::string> cuisines_;
    std::unordered_map<std::string_view, u16> cuisine_to_idx_;

    std::array<std::set<u16, SetCmp, BumpAllocator<u16>>, 20'002> sets_{};
    std::vector<int> ratings_{};

    std::array<std::byte, 10'000'000> allocator_memory_;
    size_t allocator_offset_ = 0;

    [[nodiscard]] FORCE_INLINE static FoodRatingsS& Instance() noexcept
    {
        static FoodRatingsS instance;
        return instance;
    }
};

[[nodiscard]] FORCE_INLINE constexpr bool SetCmp::operator()(
    const u16& a,
    const u16& b) const noexcept NO_SANITIZERS
{
    auto& instance = FoodRatingsS::Instance();
    int ra = instance.ratings_[a];
    int rb = instance.ratings_[b];
    if (ra != rb) return ra < rb;
    return instance.foods_[a] > instance.foods_[b];
}

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
        std::vector<std::string>& foods,
        std::vector<std::string>& cuisines,
        std::vector<int>& ratings) noexcept HOT_PATH NO_SANITIZERS
    {
        FoodRatingsS::Instance().Initialize(foods, cuisines, ratings);
    }

    FORCE_INLINE void changeRating(
        std::string_view food,
        int newRating) noexcept HOT_PATH NO_SANITIZERS
    {
        FoodRatingsS::Instance().changeRating(food, newRating);
    }

    FORCE_INLINE const std::string& highestRated(
        std::string_view cuisine) noexcept HOT_PATH NO_SANITIZERS
    {
        return FoodRatingsS::Instance().highestRated(cuisine);
    }
};
