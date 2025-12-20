#include "0131_palindrome_partitioning.hpp"
#include "gtest/gtest.h"

TEST(t0131_palindrome_partitioning, test_1)
{
    auto t = Solution{}.partition("aab");
    std::println("{}", t.size());
}
