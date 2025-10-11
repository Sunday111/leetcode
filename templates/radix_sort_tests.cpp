#include <random>

#include "gtest/gtest.h"
#include "radix_sorter.hpp"

template <typename T>
class UnstableRadixSortTest : public ::testing::Test
{
protected:
    static constexpr unsigned seed = 1234;
    static constexpr size_t num_values = 20'000;
    static constexpr size_t repeat = 20;

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
        for (size_t i = 0; i != repeat; ++i)
        {
            generate_values();

            // Ascending
            custom_sorted = values;
            std_sorted = values;

            radix_sort<4>(std::span{custom_sorted});
            std::ranges::sort(std_sorted, std::less{});
            ASSERT_EQ(custom_sorted, std_sorted);

            // Descending
            custom_sorted = values;
            std_sorted = values;

            radix_sort<4, 0xFFFFFFFF, SortOrder::Descending>(
                std::span{custom_sorted});
            std::ranges::sort(std_sorted, std::greater{});
            ASSERT_EQ(custom_sorted, std_sorted);
        }
    }
};

using TestTypes = ::testing::Types<int16_t, int32_t, uint16_t, uint32_t>;
TYPED_TEST_SUITE(UnstableRadixSortTest, TestTypes);

TYPED_TEST(UnstableRadixSortTest, RandomizedCorrectness)
{
    this->run_sort_tests();
}

template <auto kBitsPerPass, auto kNumPasses>
struct StableSortParams
{
    [[nodiscard]] FORCE_INLINE static constexpr auto num_sorted_bits() noexcept
    {
        return kBitsPerPass * kNumPasses;
    }
    [[nodiscard]] FORCE_INLINE static constexpr auto bits_per_pass() noexcept
    {
        return kBitsPerPass;
    }
    [[nodiscard]] FORCE_INLINE static constexpr auto num_passes() noexcept
    {
        return kNumPasses;
    }
};

template <typename T>
class StableRadixSortTest : public ::testing::Test
{
protected:
    static constexpr unsigned seed = 1234;
    static constexpr size_t num_values = 20'000;
    static constexpr size_t repeat = 20;

    std::mt19937 rnd{seed};
    std::uniform_int_distribution<u32> distr;

    static constexpr u32 kSizeA = T::num_sorted_bits();
    static constexpr u32 kSizeB = 32 - kSizeA;

    std::vector<u32> values;
    std::vector<u32> custom_sorted;
    std::vector<u32> std_sorted;

    void generate_values()
    {
        values.clear();
        values.reserve(num_values);
        for (size_t i = 0; i < num_values; ++i)
        {
            u32 a = distr(rnd) % (1 << kSizeA);
            u32 b = distr(rnd) % (1 << kSizeB);
            u32 v = (b << kSizeA) | a;
            values.emplace_back(v);
        }
    }

    template <u32 kMask, template <typename> typename Cmp>
    [[nodiscard]] FORCE_INLINE static constexpr bool mask_and_compare(
        u32 v1,
        u32 v2) noexcept
    {
        return Cmp<u32>{}((v1 & kMask), (v2 & kMask));
    }

    void run_sort_tests()
    {
        for (size_t i = 0; i != repeat; ++i)
        {
            generate_values();

            // Ascending
            custom_sorted = values;
            std_sorted = values;

            constexpr auto kMask = u32{0xFFFFFFFF} >> kSizeB;

            stable_radix_sort<T::bits_per_pass(), T::num_passes()>(
                reinterpret_range<u32>(std::span{custom_sorted}));
            std::ranges::stable_sort(
                std_sorted,
                mask_and_compare<kMask, std::less>);
            ASSERT_EQ(custom_sorted, std_sorted);

            // Descending
            custom_sorted = values;
            std_sorted = values;

            stable_radix_sort<
                T::bits_per_pass(),
                T::num_passes(),
                SortOrder::Descending>(
                reinterpret_range<u32>(std::span{custom_sorted}));
            std::ranges::stable_sort(
                std_sorted,
                mask_and_compare<kMask, std::greater>);
            ASSERT_EQ(custom_sorted, std_sorted);
        }
    }
};

using StableTestTypes = ::testing::Types<
    StableSortParams<3, 2>,
    StableSortParams<7, 2>,
    StableSortParams<4, 5>>;

TYPED_TEST_SUITE(StableRadixSortTest, StableTestTypes);

TYPED_TEST(StableRadixSortTest, RandomizedCorrectness)
{
    this->run_sort_tests();
}
