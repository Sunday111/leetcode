#include <array>
#include <type_traits>
#include <utility>

#include "graph/lca.hpp"
#include "gtest/gtest.h"
#include "integral_aliases.hpp"
#include "signed_integral_aliases.hpp"
#include "sparse_table/st_required_buffer_size.hpp"

template <typename T>
class LcaTypedTest : public ::testing::Test
{
};

using LcaValueTypes = ::testing::Types<u8, u16, u32, u64, i8, i16, i32, i64>;
TYPED_TEST_SUITE(LcaTypedTest, LcaValueTypes);

TYPED_TEST(LcaTypedTest, AllVertexPairs)
{
    using Index = std::make_unsigned_t<TypeParam>;
    using Entry = std::pair<Index, Index>;
    const Entry tour[]{{0, 2}, {1, 0}, {0, 2}, {1, 1}, {2, 3}, {1, 1}, {0, 2}};
    const u16 first[]{1, 3, 0, 4};
    std::array<Entry, st_required_buffer_size(7)> buffer{};
    const auto table = lca_preprocess(tour, u16{7}, buffer.data());
    const std::array<std::array<Index, 4>, 4> expected{
        {{0, 2, 2, 2}, {2, 1, 2, 1}, {2, 2, 2, 2}, {2, 1, 2, 3}}};
    for (Index u = 0; u != 4; ++u)
    {
        for (Index v = 0; v != 4; ++v)
        {
            EXPECT_EQ(lca(table, first, u, v), expected.at(u).at(v));
        }
    }
}

TEST(Lca, SingleVertex)
{
    const std::pair<u16, u8> tour[]{{0, 0}};
    const u32 first[]{0};
    std::pair<u16, u8> buffer[1]{};
    const auto table = lca_preprocess(tour, 1U, buffer);
    EXPECT_EQ(lca(table, first, 0, 0), 0);
}

TEST(Lca, TourPositionsExceedVertexIndexRange)
{
    using Entry = std::pair<u16, u8>;
    constexpr u16 length = 509;
    std::array<Entry, length> tour{};
    std::array<u16, 255> first{};
    tour.front() = {0, 254};
    for (u8 i = 0; i != 254; ++i)
    {
        const auto position = static_cast<u16>(2 * i + 1);
        first.at(i) = position;
        tour.at(position) = {1, i};
        tour.at(position + 1) = {0, 254};
    }
    std::array<Entry, st_required_buffer_size(length)> buffer{};
    const auto table = lca_preprocess(tour.data(), length, buffer.data());
    EXPECT_EQ(lca(table, first.data(), 250, 253), 254);
    EXPECT_EQ(lca(table, first.data(), 253, 250), 254);
    EXPECT_EQ(lca(table, first.data(), 253, 253), 253);
    EXPECT_EQ(lca(table, first.data(), 253, 254), 254);
}

TEST(Lca, WorksAtCompileTime)
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
            const unsigned first[]{1, 3, 0};
            std::pair<unsigned, unsigned> buffer[15]{};
            const auto table = lca_preprocess(tour, 5U, buffer);
            return lca(table, first, 0, 1) == 2 && lca(table, first, 0, 0) == 0;
        }());
}
