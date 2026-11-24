#include <algorithm>
#include <array>
#include <type_traits>
#include <utility>

#include "graph/euler_tour.hpp"
#include "graph/graph_from_edges.hpp"
#include "graph/lca.hpp"
#include "gtest/gtest.h"
#include "integral_aliases.hpp"
#include "signed_integral_aliases.hpp"
#include "sparse_table/st_range.hpp"
#include "sparse_table/st_required_buffer_size.hpp"

template <typename T>
class LcaPreprocessTypedTest : public ::testing::Test
{
};

using LcaPreprocessValueTypes =
    ::testing::Types<u8, u16, u32, u64, i8, i16, i32, i64>;
TYPED_TEST_SUITE(LcaPreprocessTypedTest, LcaPreprocessValueTypes);

TYPED_TEST(LcaPreprocessTypedTest, AllPairsMatchParentWalk)
{
    using T = TypeParam;
    using Index = std::make_unsigned_t<T>;
    using Entry = std::pair<Index, Index>;
    constexpr Index n = 8;
    constexpr u32 length = euler_tour_required_buffer_size(n);
    const std::array<std::array<T, 2>, 7> edges{
        {{0, 1}, {1, 2}, {1, 3}, {3, 4}, {4, 5}, {3, 6}, {6, 7}}};
    std::array<Index, n> degree{}, offset{}, depth{}, stack{}, next_link{};
    std::array<u32, n> first{};
    std::array<Index, 14> links{};
    std::array<Entry, length> tour{};
    graph_from_edges(
        edges.data(),
        7,
        n,
        degree.data(),
        offset.data(),
        links.data());
    euler_tour(
        n,
        3,
        degree.data(),
        offset.data(),
        links.data(),
        tour.data(),
        depth.data(),
        first.data(),
        stack.data(),
        next_link.data());
    const auto original_tour = tour;
    std::array<Entry, st_required_buffer_size(length) + 1> buffer{};
    buffer.fill({99, 99});
    const auto table = lca_preprocess(tour.data(), length, buffer.data());
    EXPECT_EQ(table.x, buffer.data());
    EXPECT_EQ(table.size, length);

    const std::array<Index, n> parent{1, 3, 1, 3, 3, 4, 3, 6};
    const std::array<Index, n> expected_depth{2, 1, 2, 0, 1, 2, 1, 2};
    for (Index u = 0; u != n; ++u)
    {
        for (Index v = 0; v != n; ++v)
        {
            Index a = u, b = v;
            while (expected_depth.at(a) > expected_depth.at(b))
            {
                a = parent.at(a);
            }
            while (expected_depth.at(b) > expected_depth.at(a))
            {
                b = parent.at(b);
            }
            while (a != b)
            {
                a = parent.at(a);
                b = parent.at(b);
            }
            const auto begin = std::min(first.at(u), first.at(v));
            const auto end = std::max(first.at(u), first.at(v)) + 1;
            EXPECT_EQ(
                st_range(table, begin, end),
                (Entry{expected_depth.at(a), a}))
                << "u=" << +u << " v=" << +v;
        }
    }
    EXPECT_EQ(tour, original_tour);
    EXPECT_EQ(buffer.back(), (Entry{99, 99}));
}

TEST(LcaPreprocess, EmptyTour)
{
    const auto table = lca_preprocess<u16, u32, u8>(nullptr, 0, nullptr);
    EXPECT_EQ(table.x, nullptr);
    EXPECT_EQ(table.size, 0);
}

TEST(LcaPreprocess, SingleVertex)
{
    const std::pair<u16, u8> tour[]{{0, 0}};
    std::pair<u16, u8> buffer[1]{};
    const auto table = lca_preprocess(tour, 1U, buffer);
    EXPECT_EQ(st_range(table, 0, 1), (std::pair<u16, u8>{0, 0}));
}

TEST(LcaPreprocess, TourPositionsExceedVertexIndexRange)
{
    constexpr u8 n = 255;
    constexpr u16 length = euler_tour_required_buffer_size(n);
    std::array<std::array<u8, 2>, n - 1> edges{};
    for (u8 i = 0; i != n - 1; ++i)
    {
        edges.at(i) = {static_cast<u8>(n - 1), i};
    }
    std::array<u8, n> degree{}, stack{}, next_link{};
    std::array<u16, n> offset{}, depth{}, first{};
    std::array<u8, 2 * (n - 1)> links{};
    using Entry = std::pair<u16, u8>;
    std::array<Entry, length> tour{};
    graph_from_edges(
        edges.data(),
        n - 1,
        n,
        degree.data(),
        offset.data(),
        links.data());
    euler_tour(
        n,
        n - 1,
        degree.data(),
        offset.data(),
        links.data(),
        tour.data(),
        depth.data(),
        first.data(),
        stack.data(),
        next_link.data());
    EXPECT_EQ(first.at(253), 507);
    EXPECT_EQ(depth.at(253), 1);
    EXPECT_EQ(depth.back(), 0);
    std::array<Entry, st_required_buffer_size(length)> buffer{};
    const auto table = lca_preprocess(tour.data(), length, buffer.data());
    EXPECT_EQ(
        st_range(table, first.at(250), first.at(253) + 1),
        (Entry{0, 254}));
    EXPECT_EQ(
        st_range(table, first.at(253), first.at(253) + 1),
        (Entry{1, 253}));
}

TEST(LcaPreprocess, WorksAtCompileTime)
{
    static_assert(
        []
        {
            const std::pair<unsigned, unsigned> tour[]{
                {0, 2},
                {1, 0},
                {0, 2},
                {1, 1},
                {0, 2}};
            std::pair<unsigned, unsigned> buffer[15]{};
            const auto table = lca_preprocess(tour, 5U, buffer);
            return st_range(table, 1, 4) == std::pair{0U, 2U};
        }());
}
