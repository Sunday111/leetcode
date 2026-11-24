#include <array>
#include <cstddef>
#include <type_traits>
#include <utility>
#include <vector>

#include "graph/euler_tour.hpp"
#include "graph/graph_from_edges.hpp"
#include "gtest/gtest.h"
#include "integral_aliases.hpp"
#include "signed_integral_aliases.hpp"

template <typename T>
class EulerTourTypedTest : public ::testing::Test
{
};

using EulerTourValueTypes =
    ::testing::Types<u8, u16, u32, u64, i8, i16, i32, i64>;
TYPED_TEST_SUITE(EulerTourTypedTest, EulerTourValueTypes);

TYPED_TEST(EulerTourTypedTest, RecordsReturnsAndPreservesGraph)
{
    using T = TypeParam;
    using Index = std::make_unsigned_t<T>;
    using Entry = std::pair<Index, Index>;
    constexpr Index n = 7;
    const std::array<std::array<T, 2>, 6> edges{
        {{0, 1}, {1, 2}, {1, 3}, {3, 4}, {4, 5}, {3, 6}}};
    std::array<Index, n> degree{}, offset{};
    std::array<Index, 12> links{};
    graph_from_edges(
        edges.data(),
        6,
        n,
        degree.data(),
        offset.data(),
        links.data());
    const auto original_degree = degree;
    const auto original_offset = offset;
    const auto original_links = links;
    std::array<Entry, euler_tour_required_buffer_size(n) + 1> tour{};
    std::array<Index, n + 1> stack{}, next_link{}, depth{};
    std::array<u32, n + 1> first{};
    depth.fill(99);
    first.fill(99);
    tour.fill({99, 99});
    stack.fill(99);
    next_link.fill(99);

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
    EXPECT_EQ(
        tour,
        (std::array<Entry, 14>{
            {{0, 3},
             {1, 1},
             {2, 0},
             {1, 1},
             {2, 2},
             {1, 1},
             {0, 3},
             {1, 4},
             {2, 5},
             {1, 4},
             {0, 3},
             {1, 6},
             {0, 3},
             {99, 99}}}));
    EXPECT_EQ(depth, (std::array<Index, 8>{2, 1, 2, 0, 1, 2, 1, 99}));
    EXPECT_EQ(first, (std::array<u32, 8>{2, 1, 4, 0, 7, 8, 11, 99}));

    euler_tour(
        n,
        0,
        degree.data(),
        offset.data(),
        links.data(),
        tour.data(),
        depth.data(),
        first.data(),
        stack.data(),
        next_link.data());
    EXPECT_EQ(
        tour,
        (std::array<Entry, 14>{
            {{0, 0},
             {1, 1},
             {2, 2},
             {1, 1},
             {2, 3},
             {3, 4},
             {4, 5},
             {3, 4},
             {2, 3},
             {3, 6},
             {2, 3},
             {1, 1},
             {0, 0},
             {99, 99}}}));
    EXPECT_EQ(depth, (std::array<Index, 8>{0, 1, 2, 2, 3, 4, 3, 99}));
    EXPECT_EQ(first, (std::array<u32, 8>{0, 1, 2, 4, 5, 6, 9, 99}));
    EXPECT_EQ(stack.back(), 99);
    EXPECT_EQ(next_link.back(), 99);
    EXPECT_EQ(degree, original_degree);
    EXPECT_EQ(offset, original_offset);
    EXPECT_EQ(links, original_links);
}

TEST(EulerTour, EmptyTree)
{
    euler_tour<u32, u32, u32, u32, u32>(
        0,
        0,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr);
}

TEST(EulerTour, SingleVertex)
{
    const u8 degree[]{0};
    const u32 offset[]{0};
    using Entry = std::pair<u16, u16>;
    std::array<Entry, 2> tour{{{99, 99}, {99, 99}}};
    std::array<u16, 2> stack{99, 99};
    std::array<u8, 2> next_link{99, 99};
    std::array<u16, 2> depth{99, 99};
    std::array<u32, 2> first{99, 99};
    euler_tour<u16, u8, u32>(
        1,
        0,
        degree,
        offset,
        nullptr,
        tour.data(),
        depth.data(),
        first.data(),
        stack.data(),
        next_link.data());
    EXPECT_EQ(tour, (std::array<Entry, 2>{{{0, 0}, {99, 99}}}));
    EXPECT_EQ(depth, (std::array<u16, 2>{0, 99}));
    EXPECT_EQ(first, (std::array<u32, 2>{0, 99}));
    EXPECT_EQ(stack.back(), 99);
    EXPECT_EQ(next_link.back(), 99);
}

TEST(EulerTour, StarPreservesLinkOrder)
{
    const u8 degree[]{1, 1, 4, 1, 1};
    const u16 offset[]{0, 1, 2, 6, 7};
    const u8 links[]{2, 2, 4, 1, 3, 0, 2, 2};
    using Entry = std::pair<u8, u8>;
    std::array<Entry, 9> tour{};
    u8 stack[5]{}, next_link[5]{};
    std::array<u8, 5> depth{};
    std::array<u16, 5> first{};
    euler_tour(
        u8{5},
        2,
        degree,
        offset,
        links,
        tour.data(),
        depth.data(),
        first.data(),
        stack,
        next_link);
    EXPECT_EQ(
        tour,
        (std::array<Entry, 9>{
            {{0, 2},
             {1, 4},
             {0, 2},
             {1, 1},
             {0, 2},
             {1, 3},
             {0, 2},
             {1, 0},
             {0, 2}}}));
    EXPECT_EQ(depth, (std::array<u8, 5>{1, 1, 0, 1, 1}));
    EXPECT_EQ(first, (std::array<u16, 5>{7, 3, 0, 5, 1}));
}

TEST(EulerTour, DeepTreeUsesCallerBuffers)
{
    constexpr u16 n = 50'000;
    std::vector<std::array<u16, 2>> edges(n - 1);
    for (u16 i = 0; i != n - 1; ++i)
    {
        edges.at(i) = {i, static_cast<u16>(i + 1)};
    }
    std::vector<u8> degree(n);
    std::vector<u32> offset(n);
    std::vector<u16> links(2 * edges.size());
    graph_from_edges(
        edges.data(),
        static_cast<u32>(edges.size()),
        n,
        degree.data(),
        offset.data(),
        links.data());
    constexpr auto tour_size = euler_tour_required_buffer_size(n);
    using Entry = std::pair<u16, u16>;
    std::vector<Entry> tour(tour_size + 1, {60'000, 60'000});
    std::vector<u16> stack(n + 1, 60'000);
    std::vector<u8> next_link(n + 1, 99);
    std::vector<u16> depth(n + 1, 60'000);
    std::vector<u32> first(n + 1, 100'000);
    euler_tour(
        n,
        0,
        degree.data(),
        offset.data(),
        links.data(),
        tour.data(),
        depth.data(),
        first.data(),
        stack.data(),
        next_link.data());
    for (std::size_t i = 0; i != tour_size; ++i)
    {
        const auto vertex = static_cast<u16>(i < n ? i : tour_size - 1 - i);
        EXPECT_EQ(tour.at(i), (Entry{vertex, vertex}));
    }
    for (u16 i = 0; i != n; ++i)
    {
        EXPECT_EQ(depth.at(i), i);
        EXPECT_EQ(first.at(i), i);
    }
    EXPECT_EQ(depth.back(), 60'000);
    EXPECT_EQ(first.back(), 100'000);
    EXPECT_EQ(tour.back(), (Entry{60'000, 60'000}));
    EXPECT_EQ(stack.back(), 60'000);
    EXPECT_EQ(next_link.back(), 99);
}

TEST(EulerTour, WorksAtCompileTime)
{
    static_assert(
        []
        {
            const unsigned degree[]{1, 1};
            const unsigned offset[]{0, 1};
            const unsigned links[]{1, 0};
            std::pair<unsigned, unsigned> tour[3]{};
            unsigned stack[2]{}, next_link[2]{}, depth[2]{}, first[2]{};
            euler_tour(
                2U,
                1,
                degree,
                offset,
                links,
                tour,
                depth,
                first,
                stack,
                next_link);
            return tour[0] == std::pair{0U, 1U} &&
                   tour[1] == std::pair{1U, 0U} &&
                   tour[2] == std::pair{0U, 1U} && depth[0] == 1 &&
                   depth[1] == 0 && first[0] == 1 && first[1] == 0;
        }());
}
