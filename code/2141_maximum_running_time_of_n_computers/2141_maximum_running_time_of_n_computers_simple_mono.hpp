#include <algorithm>
#include <cstdint>
#include <ranges>
#include <span>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

// Find an iterator to the first
template <typename Range, typename Proj>
[[nodiscard]] FORCE_INLINE constexpr auto bisectFirstFalse(
    Range&& range,
    Proj&& proj) noexcept
{
    return std::ranges::lower_bound(
        std::forward<Range>(range),
        false,
        std::greater{},
        std::forward<Proj>(proj));
}

template <typename Range, typename Proj>
[[nodiscard]] FORCE_INLINE constexpr auto bisectLastTrue(
    Range&& range,
    Proj&& proj) noexcept
{
    return bisectFirstFalse(
               std::forward<Range>(range),
               std::forward<Proj>(proj)) -
           1;
}

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

template <typename To, typename From, std::size_t extent = std::dynamic_extent>
    requires(sizeof(To) == sizeof(From))
[[nodiscard]] FORCE_INLINE static auto reinterpret_range(
    std::span<From, extent> in) noexcept
{
    return std::span<To, extent>{
        reinterpret_cast<To*>(in.data()),  // NOLINT
        in.size()};
}

template <typename To, typename From, typename Allocator>
    requires(sizeof(To) == sizeof(From))
[[nodiscard]] FORCE_INLINE static std::span<To> reinterpret_range(
    std::vector<From, Allocator>& v) noexcept
{
    return reinterpret_range<To>(std::span{v});
}

inline static constexpr auto sum =
    []<typename Range>(
        Range&& range,
        auto init = std::ranges::range_value_t<Range>{}) INLINE_LAMBDA
{
    for (auto&& v : std::forward<Range>(range))
    {
        init += v;
    }

    return init;
};

class Solution
{
public:
    [[nodiscard]] static constexpr u64 maxRunTime(
        u32 n,
        std::vector<int>& batteries_) noexcept
    {
        auto batteries = reinterpret_range<u32>(batteries_);
        std::ranges::sort(batteries, std::greater{});

        const std::span<const u32> active = batteries.first(n);
        const std::span<const u32> swaps = batteries.last(batteries.size() - n);
        if (swaps.empty()) return active.back();

        const u64 total = sum(batteries, u64{0});
        if (n == 1) return total;

        auto test = [&](u64 target) -> bool
        {
            if (active.back() >= target) return true;

            u32 rem = 0, next = 0;

            for (u32 charge : active | std::views::reverse)
            {
                if (charge >= target) break;

                u64 need = target - charge;
                while (need > rem && next != swaps.size())
                {
                    need -= rem;
                    rem = swaps[next++];
                }

                if (need > rem) return false;
                rem -= need;
            }

            return true;
        };

        return *bisectLastTrue(
            std::views::iota(u64{batteries.back()}, (total / u64{n}) + 1),
            test);
    }
};
