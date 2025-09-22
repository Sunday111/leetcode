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

#define FORCE_INLINE inline __attribute__((always_inline))

inline constexpr auto toInt = [](std::integral auto v)
{
    return static_cast<int>(v);
};

template <typename T>
inline static auto nodesPool =  // NOLINT
    []
{
    using Node = typename std::set<T>::node_type;
    std::vector<Node> nodes;
    nodes.reserve(100'001);
    return nodes;
}();

template <typename T>
[[nodiscard]] FORCE_INLINE constexpr auto takeLast(T& arr) noexcept
{
    auto r = std::move(arr.back());
    arr.pop_back();
    return r;
}

template <typename T, typename... Args>
FORCE_INLINE constexpr void setEmplace(std::set<T>& s, Args&&... args) noexcept
{
    if (nodesPool<T>.empty())
    {
        s.emplace(std::forward<Args>(args)...);
    }
    else
    {
        auto node = takeLast(nodesPool<T>);
        node.value() = {std::forward<Args>(args)...};
        s.insert(std::move(node));
    }
}

template <typename T>
FORCE_INLINE constexpr void setErase(std::set<T>& s, const T& value) noexcept
{
    nodesPool<T>.emplace_back(s.extract(value));
}

struct MovieInfo
{
    u32 movieId;
    std::set<PriceAndShop> pricesAndShops;
    std::unordered_map<ShopID, Price> shopsAndPrices;
    std::unordered_map<ShopID, Price> rentedShopsAndPrices;

    FORCE_INLINE constexpr void add(ShopID shop, Price price) noexcept
    {
        setEmplace(pricesAndShops, price, shop);
        shopsAndPrices.emplace(shop, price);
    }

    FORCE_INLINE constexpr Price rent(u32 shop) noexcept
    {
        auto it = shopsAndPrices.find(shop);
        auto price = it->second;
        shopsAndPrices.erase(it);
        setErase(pricesAndShops, {price, shop});
        rentedShopsAndPrices[shop] = price;
        return price;
    }

    FORCE_INLINE constexpr Price returnCopy(u32 shop) noexcept
    {
        auto it = rentedShopsAndPrices.find(shop);
        auto price = it->second;
        rentedShopsAndPrices.erase(it);
        setEmplace(pricesAndShops, price, shop);
        shopsAndPrices.emplace(shop, price);
        return price;
    }

    FORCE_INLINE constexpr std::vector<int> top_cheapest() const noexcept
    {
        return std::ranges::to<std::vector>(
            pricesAndShops | std::views::take(5) |
            std::views::transform(&PriceAndShop::second) |
            std::views::transform(toInt));
    }
};

class MovieRentingSystem
{
public:
    std::unordered_map<MovieID, MovieInfo> available;
    std::set<PriceShopMovie> rented;

    constexpr MovieRentingSystem(
        u32,
        std::vector<std::vector<int>>& entries) noexcept
    {
        for (auto& entry : entries)
        {
            auto shop = static_cast<ShopID>(entry[0]);
            auto movie = static_cast<MovieID>(entry[1]);
            auto price = static_cast<Price>(entry[2]);
            available[movie].add(shop, price);
        }
    }

    constexpr std::vector<int> search(MovieID movie) noexcept
    {
        return available[movie].top_cheapest();
    }

    constexpr void rent(ShopID shop, MovieID movie) noexcept
    {
        auto price = available[movie].rent(shop);
        setEmplace(rented, price, shop, movie);
    }

    constexpr void drop(ShopID shop, MovieID movie) noexcept
    {
        auto price = available[movie].returnCopy(shop);
        setErase(rented, {price, shop, movie});
    }

    // Returns 5 cheapest rented movies as a  list of pairs [shop, movie]
    constexpr std::vector<std::vector<int>> report() const noexcept
    {
        return std::ranges::to<std::vector>(
            rented | std::views::take(5) |
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
