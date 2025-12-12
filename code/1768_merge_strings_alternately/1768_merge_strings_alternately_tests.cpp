#include "1768_merge_strings_alternately_simple.hpp"
#include "1768_merge_strings_alternately_sse2.hpp"
#include "gtest/gtest.h"
#include "strings_for_testing.hpp"

TEST(t1768_merge_strings_alternately, test_simple)
{
    auto& strings = StringsForTesting::Get().strings;
    for (u32 i = 0; i != strings.size(); ++i)
    {
        auto& a = strings[i];
        for (u32 j = i + 1; j != strings.size(); ++j)
        {
            auto& b = strings[j];
            auto r = simple::Solution{}.mergeAlternately(a, b);

            ASSERT_EQ(r.size(), a.size() + b.size());
            size_t l1 = std::min(a.size(), b.size());
            for (u32 k = 0; k != l1; ++k)
            {
                ASSERT_EQ(a[k], r[k * 2]);
                ASSERT_EQ(b[k], r[k * 2 + 1]);
            }
        }
    }
}

TEST(t1768_merge_strings_alternately, DISABLED_test_sse2)
{
    auto& strings = StringsForTesting::Get().strings;
    for (u32 i = 0; i != strings.size(); ++i)
    {
        auto& a = strings[i];
        for (u32 j = i + 1; j != strings.size(); ++j)
        {
            auto& b = strings[j];
            auto r = solution_sse2::Solution{}.mergeAlternately(a, b);

            ASSERT_EQ(r.size(), a.size() + b.size());
            size_t l1 = std::min(a.size(), b.size());
            for (u32 k = 0; k != l1; ++k)
            {
                ASSERT_EQ(a[k], r[k * 2]);
                ASSERT_EQ(b[k], r[k * 2 + 1]);
            }
        }
    }
}
