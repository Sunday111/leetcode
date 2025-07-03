#pragma once

#include <atomic>
#include <functional>

class FizzBuzz
{
private:
    int n;
    std::atomic<int> i{1};

public:
    explicit FizzBuzz(int n) : n{n} {}

    // printFizz() outputs "fizz".
    void fizz(const std::function<void()>& printFizz)
    {
        while (true)
        {
            int v = i.load(std::memory_order_relaxed);
            if (v > n) break;
            if ((v % 3) == 0 && (v % 5 != 0))
            {
                printFizz();
                i.store(v + 1, std::memory_order_relaxed);
            }
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(const std::function<void()>& printBuzz)
    {
        while (true)
        {
            int v = i.load(std::memory_order_relaxed);
            if (v > n) break;
            if ((v % 3) != 0 && (v % 5 == 0))
            {
                printBuzz();
                i.store(v + 1, std::memory_order_relaxed);
            }
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(const std::function<void()>& printFizzBuzz)
    {
        while (true)
        {
            int v = i.load(std::memory_order_relaxed);
            if (v > n) break;
            if ((v % 3) == 0 && (v % 5 == 0))
            {
                printFizzBuzz();
                i.store(v + 1, std::memory_order_relaxed);
            }
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(const std::function<void(int)>& printNumber)
    {
        while (true)
        {
            int v = i.load(std::memory_order_relaxed);
            if (v > n) break;
            if ((v % 3) != 0 && (v % 5 != 0))
            {
                printNumber(v);
                i.store(v + 1, std::memory_order_relaxed);
            }
        }
    }
};
