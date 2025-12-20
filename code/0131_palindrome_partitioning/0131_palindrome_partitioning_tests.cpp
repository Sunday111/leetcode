#include "0131_palindrome_partitioning.hpp"
#include "gtest/gtest.h"

TEST(t0131_palindrome_partitioning, test_1)
{
    auto t = Solution{}.partition("aab");

    for (auto& x : t)
    {
        std::println("{}", x);
    }
    std::println("{}", t.size());
}

TEST(t0131_palindrome_partitioning, test_2)
{
    auto t = Solution{}.partition("aaa");

    for (auto& x : t)
    {
        std::println("{}", x);
    }
    std::println("{}", t.size());
}
