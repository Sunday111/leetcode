#include <algorithm>
#include <latch>
#include <random>
#include <thread>

#include "1117_building_h2o.hpp"
#include "gtest/gtest.h"

TEST(t1117_building_h2o, test_1)
{
    constexpr size_t m = 15'000;

    const auto input = []
    {
        const unsigned seed = std::random_device{}();
        std::println("Generating input with seed: {}", seed);
        std::mt19937_64 rnd{seed};
        std::string input;
        input.reserve(3 * m);
        input.resize(2 * m, 'H');
        input.resize(3 * m, 'O');
        std::ranges::shuffle(input, rnd);
        return input;
    }();

    std::array<uint8_t, m * 3> results{};
    std::atomic<uint32_t> num_results = 0;

    std::function release_h = [&]()
    {
        num_results.fetch_add(1);
    };

    std::function release_o = [&]()
    {
        results[num_results.fetch_add(1)] = 1;
    };

    {
        std::println("Creating {} threads...", input.size());
        std::vector<std::jthread> threads;
        std::latch start{static_cast<std::ptrdiff_t>(input.size()) + 1};

        H2O s;
        for (char c : input)
        {
            if (c == 'H')
            {
                threads.emplace_back(
                    [&]()
                    {
                        start.arrive_and_wait();
                        s.hydrogen(release_h);
                    });
            }
            else
            {
                threads.emplace_back(
                    [&]()
                    {
                        start.arrive_and_wait();
                        s.oxygen(release_o);
                    });
            }
        }

        std::println("GO!");
        start.arrive_and_wait();
    }

    std::println("Checking results");
    ASSERT_EQ(num_results, m * 3);

    uint32_t sum = results.front();
    for (size_t i = 1; i != results.size(); ++i)
    {
        if (i % 3 == 0)
        {
            ASSERT_EQ(sum, 1);
            sum = 0;
        }

        sum += results[i];
    }
}
