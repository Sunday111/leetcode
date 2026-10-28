#include <algorithm>
#include <cstddef>
#include <numeric>
#include <vector>

#include "1409_queries_on_a_permutation_with_key.hpp"
#include "gtest/gtest.h"

TEST(t1409, Example)
{
    std::vector<int> queries{3, 1, 2, 1};
    EXPECT_EQ(
        Solution::processQueries(queries, 5),
        (std::vector<int>{2, 1, 2, 1}));
    EXPECT_EQ(queries, (std::vector<int>{3, 1, 2, 1}));
}

TEST(t1409, MatchesMoveToFrontReference)
{
    for (uint16_t m = 1; m != 9; ++m)
    {
        SCOPED_TRACE(m);
        std::vector<int> permutation(m);
        std::iota(permutation.begin(), permutation.end(), 1);
        std::vector<int> queries;
        std::vector<int> expected;
        const auto count = static_cast<uint16_t>(3 * m);
        for (uint16_t i = 0; i != count; ++i)
        {
            const int value = (i + m / 2) % m + 1;
            queries.push_back(value);
            const auto position = std::ranges::find(permutation, value);
            expected.push_back(
                static_cast<int>(position - permutation.begin()));
            permutation.erase(position);
            permutation.insert(permutation.begin(), value);
        }
        EXPECT_EQ(Solution::processQueries(queries, m), expected);
    }
}

TEST(t1409, RepeatedQuery)
{
    std::vector<int> queries{4, 4, 4, 4};
    EXPECT_EQ(
        Solution::processQueries(queries, 4),
        (std::vector<int>{3, 0, 0, 0}));
}
