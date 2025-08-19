#include <random>
#include <unordered_map>
#include <unordered_set>

#include "gtest/gtest.h"
#include "hash_set.hpp"

TEST(HashSetTest, Simple)
{
    constexpr unsigned seed = 1234;
    constexpr size_t num_values = 20'000;
    constexpr size_t num_passes = 200;
    std::mt19937 rnd{seed};
    std::uniform_int_distribution<u32> distr;

    std::vector<u32> values;
    std::unordered_set<u32> std_set;

    static constexpr u32 kCapacity = 1 << 16;
    static std::array<u32, kCapacity> arr;
    HashSet<kCapacity, u32, u32{}, ~u32{}> my_set{std::span{arr}};

    auto generate_values = [&]
    {
        values.clear();
        values.reserve(num_values);
        for (size_t i = 0; i < num_values; ++i) values.emplace_back(distr(rnd));
    };

    for (size_t pass = 0; pass < num_passes; ++pass)
    {
        generate_values();
        my_set.Init();
        std_set.clear();

        for (auto value : values)
        {
            ASSERT_EQ(std_set.contains(value), my_set.contains(value));
            std_set.insert(value);
            my_set.add(value);
        }
    }
}

TEST(HashMapTest, Simple)
{
    constexpr unsigned seed = 1234;
    constexpr size_t num_values = 20'000;
    constexpr size_t num_passes = 200;
    std::mt19937 rnd{seed};
    std::uniform_int_distribution<u32> distr;

    std::vector<u32> values;
    std::unordered_map<u32, u32> std_map;

    using Value = std::pair<u32, u32>;
    static std::array<Value, 1 << 16> arr;
    constexpr u32 capacity = 1 << 16;

    constexpr auto proj = []<typename T>(T&& v) -> decltype(auto)  // NOLINT
    {
        return (v.first);
    };

    HashSet<capacity, Value, Value{}, ~u32{}, proj> my_map{arr};

    auto generate_values = [&]
    {
        values.clear();
        values.reserve(num_values);
        for (size_t i = 0; i < num_values; ++i) values.emplace_back(distr(rnd));
    };

    for (size_t pass = 0; pass < num_passes; ++pass)
    {
        generate_values();
        my_map.Init();
        std_map.clear();

        for (auto value : values)
        {
            auto a = std_map.find(value);
            auto b = my_map.find(value);

            ASSERT_EQ(a == std_map.end(), b == nullptr);

            if (b)
            {
                b->second *= 7;
                a->second *= 7;
            }
            else
            {
                std_map.emplace(value, value * 7);
                my_map.add({value, value * 7});
            }
        }
    }
}
