#include <gtest/gtest.h>

#include <limits>
#include <random>
#include <type_traits>

#include "max2.hpp"

// === Typed test fixture ===
template <typename T>
class MaxTest : public ::testing::Test
{
};

using IntegralTypes = ::testing::Types<
    int8_t,
    uint8_t,
    int16_t,
    uint16_t,
    int32_t,
    uint32_t,
    int64_t,
    uint64_t>;

TYPED_TEST_SUITE(MaxTest, IntegralTypes);

// === Fuzzy test with random inputs ===
TYPED_TEST(MaxTest, FuzzyCorrectness)
{
    using T = TypeParam;
    using Limits = std::numeric_limits<T>;
    using DT = std::conditional_t<std::is_signed_v<T>, int64_t, uint64_t>;

    constexpr size_t kNumSamples = 1000000;

    std::mt19937 rng(42);

    std::uniform_int_distribution<DT> dist{Limits::min(), Limits::max()};
    for (size_t i = 0; i != kNumSamples; ++i)
    {
        const T a = static_cast<T>(dist(rng)), b = static_cast<T>(dist(rng));
        T expected = std::max(a, b);
        T actual = max2(a, b);
        ASSERT_EQ(actual, expected) << "Failed for a=" << +a << ", b=" << +b;
    }
}
