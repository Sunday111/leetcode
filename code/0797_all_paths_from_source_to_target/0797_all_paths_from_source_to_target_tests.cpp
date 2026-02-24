#include "0797_all_paths_from_source_to_target.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t0797_all_paths_from_source_to_target, test_1)
{
    auto g = parse2DArray("[[1,2],[3],[3],[]]");
    auto expected = parse2DArray("[[0,1,3],[0,2,3]]");
    auto actual = Solution{}.allPathsSourceTarget(g);
    ASSERT_EQ(expected, actual);
}

TEST(t0797_all_paths_from_source_to_target, test_2)
{
    auto g = parse2DArray("[[4,3,1],[3,2,4],[3],[4],[]]");
    auto expected =
        parse2DArray("[[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]");
    auto actual = Solution{}.allPathsSourceTarget(g);
    ASSERT_EQ(expected, actual);
}
