#include "0043_multiply_strings.hpp"
#include "gtest/gtest.h"

TEST(t0043_multiply_strings, test_1)
{
    std::string sa, sb;
    for (uint64_t a = 0; a != 99; ++a)
    {
        sa.clear();
        std::format_to(std::back_inserter(sa), "{}", a);

        for (uint64_t b = 0; b < 10'000'000; b += 1009)
        {
            sb.clear();
            std::format_to(std::back_inserter(sb), "{}", b);

            auto r = Solution{}.multiply(sa, sb);
            // std::println("{:3} x {:3} = {}", a, b, r);
            ASSERT_EQ(std::stoi(r), a * b);
        }
    }
}
