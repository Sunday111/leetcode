#include <random>

#include "gtest/gtest.h"
#include "radix_sorter.hpp"

template <typename T>
class RadixSortTest : public ::testing::Test
{
protected:
    static constexpr unsigned seed = 1234;
    static constexpr size_t num_values = 2;
    static constexpr size_t num_passes = 20;

    std::mt19937 rnd{seed};
    std::uniform_int_distribution<T> distr;

    std::vector<T> values;
    std::vector<T> custom_sorted;
    std::vector<T> std_sorted;

    void generate_values()
    {
        values.clear();
        values.reserve(num_values);
        for (size_t i = 0; i < num_values; ++i) values.emplace_back(distr(rnd));
    }

    void run_sort_tests()
    {
        for (size_t pass = 0; pass < num_passes; ++pass)
        {
            generate_values();

            // Ascending
            custom_sorted = values;
            std_sorted = values;

            using Sorter = RadixSorter<T, SortOrder::Ascending, 4>;
            Sorter::sort(std::span{custom_sorted});
            std::ranges::sort(std_sorted, std::less{});
            ASSERT_EQ(custom_sorted, std_sorted);

            // Descending
            custom_sorted = values;
            std_sorted = values;

            using SorterDesc = RadixSorter<T, SortOrder::Descending, 4>;
            SorterDesc::sort(std::span{custom_sorted});
            std::ranges::sort(std_sorted, std::greater{});
            ASSERT_EQ(custom_sorted, std_sorted);
        }
    }
};

using TestTypes = ::testing::Types<int16_t, int32_t, uint16_t, uint32_t>;
TYPED_TEST_SUITE(RadixSortTest, TestTypes);

TYPED_TEST(RadixSortTest, RandomizedCorrectness)
{
    this->run_sort_tests();
}
