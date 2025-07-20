#include "1948_delete_duplicate_folders_in_system.hpp"
#include "gtest/gtest.h"

TEST(t1948_delete_duplicate_folders_in_system, test_1)
{
    std::vector<std::vector<std::string>> paths{
        {"a"},
        {"c"},
        {"d"},
        {"a", "b"},
        {"c", "b"},
        {"d", "a"},
    };
    auto r = Solution{}.deleteDuplicateFolder(paths);
}

TEST(t1948_delete_duplicate_folders_in_system, test_2)
{
    std::vector<std::vector<std::string>> paths{
        {{"a"},
         {"c"},
         {"a", "b"},
         {"c", "b"},
         {"a", "b", "x"},
         {"a", "b", "x", "y"},
         {"w"},
         {"w", "y"}},
    };
    auto r = Solution{}.deleteDuplicateFolder(paths);
}

TEST(t1948_delete_duplicate_folders_in_system, test_3)
{
    std::vector<std::vector<std::string>> paths{
        {"b"},
        {"f"},
        {"f", "r"},
        {"f", "r", "g"},
        {"f", "r", "g", "c"},
        {"f", "r", "g", "c", "r"},
        {"f", "o"},
        {"f", "o", "x"},
        {"f", "o", "x", "t"},
        {"f", "o", "x", "d"},
        {"f", "o", "l"},
        {"l"},
        {"l", "q"},
        {"c"},
        {"h"},
        {"h", "t"},
        {"h", "o"},
        {"h", "o", "d"},
        {"h", "o", "t"},
    };
    auto r = Solution{}.deleteDuplicateFolder(paths);
}

TEST(t1948_delete_duplicate_folders_in_system, test_4)
{
    std::vector<std::vector<std::string>> paths{
        {{"a"},
         {"a", "c"},
         {"a", "c", "x"},
         {"b"},
         {"b", "d"},
         {"b", "d", "x"}},
    };
    auto r = Solution{}.deleteDuplicateFolder(paths);
}
