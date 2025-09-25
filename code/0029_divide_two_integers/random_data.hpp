#pragma once

#include <random>
#include <vector>

#include "integral_aliases.hpp"

struct RandomData
{
    static constexpr u64 num_samples = 10'000'000;
    inline static RandomData& Instance() noexcept
    {
        static RandomData instance;
        return instance;
    }

    std::vector<std::pair<i64, i64>> values;
    RandomData()
    {
        std::mt19937_64 gen(42);  // fixed seed for reproducibility
        std::uniform_int_distribution<i32> dist_a(1, INT_MAX);

        values.reserve(num_samples);
        for (u64 i = 0; i != num_samples; ++i)
        {
            i32 a = dist_a(gen);
            i32 b = static_cast<i32>(gen()) % INT_MAX;
            values.emplace_back(a, b);
        }
    }
};
