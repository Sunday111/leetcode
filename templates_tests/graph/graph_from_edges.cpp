#include <array>
#include <limits>
#include <type_traits>
#include <vector>

#include "graph/graph_from_edges.hpp"
#include "gtest/gtest.h"
#include "integral_aliases.hpp"
#include "signed_integral_aliases.hpp"

template <typename T>
class GraphFromEdgesTypedTest : public ::testing::Test
{
};

using GraphFromEdgesValueTypes =
    ::testing::Types<u8, u16, u32, u64, i8, i16, i32, i64>;
TYPED_TEST_SUITE(GraphFromEdgesTypedTest, GraphFromEdgesValueTypes);

TYPED_TEST(GraphFromEdgesTypedTest, PreservesEdgesAndNeighbourOrder)
{
    using T = TypeParam;
    using Index = std::make_unsigned_t<T>;
    const std::array<std::array<T, 2>, 5> edges{
        {{3, 1}, {0, 3}, {1, 0}, {3, 3}, {3, 1}}};
    const auto original = edges;
    std::array<Index, 6> degree{}, offset{};
    degree.fill(99);
    offset.fill(99);
    std::array<Index, 11> links{};
    links.fill(99);

    graph_from_edges(
        edges.data(),
        Index{5},
        Index{5},
        degree.data(),
        offset.data(),
        links.data());

    const std::array<Index, 5> degrees{2, 3, 0, 5, 0};
    const std::array<Index, 5> offsets{0, 2, 5, 5, 10};
    for (Index i = 0; i != degrees.size(); ++i)
    {
        EXPECT_EQ(degree.at(i), degrees.at(i));
        EXPECT_EQ(offset.at(i), offsets.at(i));
    }
    EXPECT_EQ(links, (std::array<Index, 11>{3, 1, 3, 0, 3, 1, 0, 3, 3, 1, 99}));
    EXPECT_EQ(degree.back(), 99);
    EXPECT_EQ(offset.back(), 99);
    EXPECT_EQ(edges, original);
}

TEST(Graph, MakesEmptyGraph)
{
    using Edge = std::array<int, 2>;
    graph_from_edges<Edge, u32, u32, u32>(
        nullptr,
        0,
        0,
        nullptr,
        nullptr,
        nullptr);
}

TEST(Graph, ReusesBuffersAndResetsIsolatedNodes)
{
    using Edge = std::array<int, 2>;
    const Edge edges[]{{0, 1}, {1, 2}};
    std::array<u32, 3> degree{}, offset{};
    std::array<u32, 4> links{};
    graph_from_edges(edges, 2U, 3U, degree.data(), offset.data(), links.data());
    EXPECT_EQ(degree.at(1), 2);

    graph_from_edges<Edge, u32>(
        nullptr,
        0,
        3,
        degree.data(),
        offset.data(),
        nullptr);
    for (u32 i = 0; i != degree.size(); ++i)
    {
        EXPECT_EQ(degree.at(i), 0);
        EXPECT_EQ(offset.at(i), 0);
    }

    const Edge replacement[]{{2, 0}};
    graph_from_edges(
        replacement,
        1U,
        3U,
        degree.data(),
        offset.data(),
        links.data());
    EXPECT_EQ(degree.at(0), 1);
    EXPECT_EQ(degree.at(1), 0);
    EXPECT_EQ(degree.at(2), 1);
    EXPECT_EQ(offset.at(2), 1);
    EXPECT_EQ(links.front(), 2);
    EXPECT_EQ(links.at(1), 0);
}

TEST(Graph, AcceptsVectorEdges)
{
    const std::vector<std::vector<int>> edges{{0, 1}, {2, 3}};
    std::array<u32, 4> degree{}, offset{};
    std::array<u32, 4> links{};
    graph_from_edges(
        edges.data(),
        2U,
        4U,
        degree.data(),
        offset.data(),
        links.data());
    EXPECT_EQ(links, (std::array<u32, 4>{1, 0, 3, 2}));
    for (u32 i = 0; i != degree.size(); ++i)
    {
        EXPECT_EQ(degree.at(i), 1);
        EXPECT_EQ(offset.at(i), i);
    }
}

TEST(Graph, MakesMaximumSmallIndexNodeCount)
{
    constexpr u8 n = std::numeric_limits<u8>::max();
    constexpr u8 m = 127;
    std::array<std::array<u8, 2>, m> edges{};
    for (u8 i = 0; i != m; ++i)
    {
        edges.at(i) = {static_cast<u8>(n - 1), i};
    }
    std::array<u8, n> degree{}, offset{};
    std::array<u8, 2 * m> links{};
    graph_from_edges(
        edges.data(),
        m,
        n,
        degree.data(),
        offset.data(),
        links.data());
    EXPECT_EQ(offset.back(), m);
    EXPECT_EQ(degree.back(), m);
    for (u8 i = 0; i != m; ++i)
    {
        EXPECT_EQ(links.at(i), n - 1);
        EXPECT_EQ(links.at(m + i), i);
    }
}

TEST(Graph, UsesIndependentArrayTypes)
{
    constexpr u8 n = 150;
    constexpr u32 m = 300;
    std::array<std::array<u8, 2>, m> edges{};
    for (u32 i = 0; i != m; ++i)
    {
        edges.at(i) = {static_cast<u8>(i % n), static_cast<u8>((i + 1) % n)};
    }
    std::array<u16, n> degree{};
    std::array<u32, n> offset{};
    std::array<u8, 2 * m> links{};
    graph_from_edges(
        edges.data(),
        m,
        n,
        degree.data(),
        offset.data(),
        links.data());
    for (u8 i = 0; i != n; ++i)
    {
        EXPECT_EQ(degree.at(i), 4);
        EXPECT_EQ(offset.at(i), 4U * i);
        const u8 first = i == 0 ? 1 : static_cast<u8>(i - 1);
        const u8 second = i == 0 ? n - 1 : static_cast<u8>((i + 1) % n);
        for (u32 j = 0; j != 4; ++j)
        {
            EXPECT_EQ(links.at(offset.at(i) + j), j % 2 == 0 ? first : second);
        }
    }
}

TEST(Graph, MakesAtCompileTime)
{
    static_assert(
        []
        {
            const int edges[][2]{{0, 1}, {0, 2}};
            unsigned degree[3]{}, offset[3]{};
            unsigned links[4]{};
            graph_from_edges(edges, 2U, 3U, degree, offset, links);
            return degree[0] == 2 && offset[1] == 2 && offset[2] == 3 &&
                   links[0] == 1 && links[1] == 2 && links[2] == 0 &&
                   links[3] == 0;
        }());
}
