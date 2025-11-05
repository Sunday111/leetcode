#include <set>
#include <unordered_map>
#include <vector>

#include "bump_set.hpp"

using ShopID = u32;   // [1; 3 * 10^5]
using MovieID = u16;  // [1; 10^4]
using Price = u16;    // [1; 10^4]

using SetStorage = GlobalBufferStorage<1 << 25>;

class MovieRentingSystem
{
private:
    struct PairHash
    {
        FORCE_INLINE size_t
        operator()(const std::pair<int, int>& p) const noexcept
        {
            uint64_t v = (u64{std::bit_cast<u32>(p.first)} << 32) |
                         u64{std::bit_cast<u32>(p.second)};
            return std::hash<u64>{}(v);
        }
    };

    std::unordered_map<
        MovieID,
        ObjectWithoutDtor<BumpSet<std::pair<Price, ShopID>, SetStorage>>>
        unrented;
    ObjectWithoutDtor<BumpSet<std::tuple<Price, ShopID, MovieID>, SetStorage>>
        rented;
    std::unordered_map<std::pair<ShopID, MovieID>, Price, PairHash> prices;

public:
    MovieRentingSystem(
        [[maybe_unused]] u32 n,
        std::vector<std::vector<int>>& entries) noexcept
    {
        SetStorage::Instance().Reset();
        unrented.reserve(n);
        prices.reserve(n);

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
        if (const auto unrented_it = unrented.find(movie);
            unrented_it != unrented.end())
        {
            auto it = unrented_it->second->begin();
            auto end = unrented_it->second->end();
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
