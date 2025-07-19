#include <algorithm>

#include "1233_remove_sub_folders_from_the_filesystem.hpp"
#include "gtest/gtest.h"

TEST(t1233_remove_sub_folders_from_the_filesystem, test_1)
{
    std::vector<std::string> paths{"/a", "/a/b", "/c/d", "/c/d/e", "/c/f"};
    std::vector<std::string> expected{"/a", "/c/d", "/c/f"};
    auto actual = Solution{}.removeSubfolders(paths);
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(actual, expected);
}

TEST(t1233_remove_sub_folders_from_the_filesystem, test_2)
{
    std::vector<std::string> paths{"/a", "/a/b/c", "/a/b/d"};
    std::vector<std::string> expected{"/a"};
    auto actual = Solution{}.removeSubfolders(paths);
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(actual, expected);
}

TEST(t1233_remove_sub_folders_from_the_filesystem, test_3)
{
    std::vector<std::string> paths{"/a/b/c", "/a/b/ca", "/a/b/d"};
    std::vector<std::string> expected{"/a/b/c", "/a/b/ca", "/a/b/d"};
    auto actual = Solution{}.removeSubfolders(paths);
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(actual, expected);
}

TEST(t1233_remove_sub_folders_from_the_filesystem, test_4)
{
    std::vector<std::string> paths{
        "/aa/ab/ac/ae",
        "/aa/ab/af/ag",
        "/ap/aq/ar/as",
        "/ap/aq/ar",
        "/ap/ax/ay/az",
        "/ap",
        "/ap/aq/ar/at",
        "/aa/ab/af/ah",
        "/aa/ai/aj/ak",
        "/aa/ai/am/ao",
    };
    std::vector<std::string> expected{
        "/aa/ab/ac/ae",
        "/aa/ab/af/ag",
        "/aa/ab/af/ah",
        "/aa/ai/aj/ak",
        "/aa/ai/am/ao",
        "/ap",
    };
    auto actual = Solution{}.removeSubfolders(paths);
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(actual, expected);
}
