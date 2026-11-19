#pragma once

#include <atomic>
#include <functional>

class ZeroEvenOdd
{
private:
    int limit{};
    std::atomic<int> k = 0;

public:
    explicit ZeroEvenOdd(int n) : limit{n * 2 + 1} {}

    void zero(const std::function<void(int)>& printNumber)
    {
        while (true)
        {
            const int v = k.load(std::memory_order_relaxed) + 1;
            if (v == limit) break;
            if (v % 2)
            {
                printNumber(0);
                k.store(v, std::memory_order_relaxed);
            }
        }
    }

    void even(const std::function<void(int)>& printNumber)
    {
        while (true)
        {
            const int v = k.load(std::memory_order_relaxed) + 1;
            if (v == limit) break;
            if (v % 4 == 0)
            {
                printNumber(v / 2);
                k.store(v, std::memory_order_relaxed);
            }
        }
    }

    void odd(const std::function<void(int)>& printNumber)
    {
        while (true)
        {
            const int v = k.load(std::memory_order_relaxed) + 1;
            if (v == limit) break;
            if ((v + 2) % 4 == 0)
            {
                printNumber((v + 1) / 2);
                k.store(v, std::memory_order_relaxed);
            }
        }
    }
};
