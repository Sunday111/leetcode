#include <random>
#include <unordered_map>
#include <unordered_set>

#include "gtest/gtest.h"
#include "hash_set.hpp"

TEST(HashSetTest, Simple)
{
    constexpr unsigned seed = 1234;
    constexpr size_t num_values = 20'000;
    constexpr size_t num_passes = 20;
    std::mt19937 rnd{seed};
    std::uniform_int_distribution<u32> distr;

    std::vector<u32> values;
    std::unordered_set<u32> std_set;

    static std::array<u32, 1 << 17> arr;
    HashSet<1 << 16, u32, ~u32{0}> my_set{
        .data_ = std::span<u32, 1 << 16>{arr.data(), 1 << 16},
    };
    my_set.Init(std::numeric_limits<u32>::max());

    auto generate_values = [&]
    {
        values.clear();
        values.reserve(num_values);
        for (size_t i = 0; i < num_values; ++i) values.emplace_back(distr(rnd));
    };

    for (size_t pass = 0; pass < num_passes; ++pass)
    {
        generate_values();

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
    constexpr size_t num_passes = 20;
    std::mt19937 rnd{seed};
    std::uniform_int_distribution<u32> distr;

    std::vector<u32> values;
    std::unordered_map<u32, u32> std_map;

    using Value = std::pair<u32, u32>;
    static std::array<Value, 1 << 16> arr;
    constexpr u32 capacity = 1 << 16;

    constexpr auto proj = [](const auto& v)
    {
        return v.first;
    };
    HashSet<capacity, Value, ~u32{0}, proj> my_map{arr};
    my_map.Init(Value{0, 0});

    auto generate_values = [&]
    {
        values.clear();
        values.reserve(num_values);
        for (size_t i = 0; i < num_values; ++i) values.emplace_back(distr(rnd));
    };

    for (size_t pass = 0; pass < num_passes; ++pass)
    {
        generate_values();

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
