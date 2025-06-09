#include <algorithm>

#include "0440_kth_smallest_in_lexicographical_order.hpp"
#include "gtest/gtest.h"

TEST(t0440_kth_smallest_in_lexicographical_order, full)
{
    std::vector<std::string> strings;
    for (uint32_t n = 1; n != 1001; ++n)
    {
        strings.clear();
        strings.reserve(n);
        for (uint32_t j = 1; j <= n; ++j)
        {
            strings.push_back(std::format("{}", j));
        }
        std::ranges::sort(strings);

        for (uint32_t k = 1; k <= n; ++k)
        {
            std::println("n: {}, k: {}", n, k);
            ASSERT_EQ(
                Solution{}.findKthNumber(n, k),
                std::stoi(strings[k - 1]));
        }
    }
}
