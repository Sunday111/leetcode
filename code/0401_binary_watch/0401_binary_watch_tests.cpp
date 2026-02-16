#include "0401_binary_watch.hpp"
#include "gtest/gtest.h"

TEST(t0401_binary_watch, test_1)
{
    constexpr unsigned turned_on = 1;
    std::vector<std::string> expected{
        "0:01",
        "0:02",
        "0:04",
        "0:08",
        "0:16",
        "0:32",
        "1:00",
        "2:00",
        "4:00",
        "8:00"};

    ASSERT_EQ(Solution{}.readBinaryWatch(turned_on), expected);
}
