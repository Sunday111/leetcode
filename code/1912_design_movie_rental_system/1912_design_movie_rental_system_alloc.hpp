#include <cassert>
#include <ranges>
#include <set>
#include <unordered_map>
#include <vector>

using u16 = uint16_t;
using u32 = uint32_t;

using ShopID = u32;   // [1; 3 * 10^5]
using MovieID = u16;  // [1; 10^4]
using Price = u16;    // [1; 10^4]

using PriceAndShop = std::pair<Price, ShopID>;
using ShopAndPrice = std::pair<ShopID, Price>;
using PriceShopMovie = std::tuple<Price, ShopID, MovieID>;

inline constexpr auto toInt = [](std::integral auto v)
{
    return static_cast<int>(v);
};

#define FORCE_INLINE inline __attribute__((always_inline))

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
    template <typename> typename Comparator>
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

struct MovieInfo
{
    BumpSet<PriceAndShop, SetStorage, std::less> pricesAndShops;
    std::unordered_map<ShopID, Price> shopsAndPrices;
    std::unordered_map<ShopID, Price> rentedShopsAndPrices;

    constexpr void add(ShopID shop, Price price) noexcept
    {
        pricesAndShops->emplace(price, shop);
        shopsAndPrices.emplace(shop, price);
    }

    constexpr Price rent(u32 shop) noexcept
    {
        auto it = shopsAndPrices.find(shop);
        auto price = it->second;
        shopsAndPrices.erase(it);
        pricesAndShops->erase({price, shop});
        rentedShopsAndPrices[shop] = price;
        return price;
    }

    constexpr Price returnCopy(u32 shop) noexcept
    {
        auto it = rentedShopsAndPrices.find(shop);
        auto price = it->second;
        rentedShopsAndPrices.erase(it);
        pricesAndShops->emplace(price, shop);
        shopsAndPrices.emplace(shop, price);
        return price;
    }

    constexpr std::vector<int> top_cheapest() const noexcept
    {
        return std::ranges::to<std::vector>(
            pricesAndShops.get() | std::views::take(5) |
            std::views::transform(&PriceAndShop::second) |
            std::views::transform(toInt));
    }
};

class MovieRentingSystem
{
public:
    std::unordered_map<MovieID, MovieInfo> available;
    BumpSet<PriceShopMovie, SetStorage, std::less> rented;

    MovieRentingSystem(u32, std::vector<std::vector<int>>& entries) noexcept
    {
        SetStorage::Instance().Reset();
        for (auto& entry : entries)
        {
            auto shop = static_cast<ShopID>(entry[0]);
            auto movie = static_cast<MovieID>(entry[1]);
            auto price = static_cast<Price>(entry[2]);
            available[movie].add(shop, price);
        }
    }

    std::vector<int> search(MovieID movie) noexcept
    {
        return available[movie].top_cheapest();
    }

    void rent(ShopID shop, MovieID movie) noexcept
    {
        auto price = available[movie].rent(shop);
        rented->emplace(price, shop, movie);
    }

    void drop(ShopID shop, MovieID movie) noexcept
    {
        auto price = available[movie].returnCopy(shop);
        rented->erase({price, shop, movie});
    }

    // Returns 5 cheapest rented movies as a  list of pairs [shop, movie]
    std::vector<std::vector<int>> report() const noexcept
    {
        return std::ranges::to<std::vector>(
            rented.get() | std::views::take(5) |
            std::views::transform(
                [](const PriceShopMovie& psm)
                {
                    return std::vector{
                        toInt(std::get<1>(psm)),
                        toInt(std::get<2>(psm)),
                    };
                }));
    }
};
