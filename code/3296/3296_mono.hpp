#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <ranges>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;


namespace stdr = std::ranges;
namespace stdv = std::views;

inline static constexpr auto arith_seq_sum =
    [] [[nodiscard, gnu::always_inline]] (u64 len) noexcept -> u64
{
    return (u64{len + 1} * len) / 2;
};

inline static constexpr auto max_arith_seq_len =
    [] [[nodiscard, gnu::always_inline]] (
        u64 limit_sum,
        u32 sum_multiplier = 1) noexcept -> u32
{
    auto q = 1 + static_cast<double>(8 * limit_sum) / sum_multiplier;
    auto x = (std::sqrt(q) - 1) / 2;
    return static_cast<u32>(x);
};

class Solution
{
public:
    [[nodiscard]] u64 minNumberOfSeconds(
        const u32 target_height,
        std::vector<int>& times_) const noexcept
    {
        auto times = reinterpret_cast<std::vector<u32>&>(times_);
        stdr::sort(times);

        auto is_possible =
            [&] [[nodiscard, gnu::always_inline]] (u64 max_time) -> bool
        {
            u32 acc_height = 0;
            for (auto t : times)
            {
                acc_height += max_arith_seq_len(max_time, t);
                if (acc_height >= target_height || t > max_time) break;
            }
            return acc_height >= target_height;
        };

        return *stdr::lower_bound(
            stdv::iota(u64{1}, arith_seq_sum(target_height) * times[0]),
            true,
            std::less{},
            is_possible);
    }
};
