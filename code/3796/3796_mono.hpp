#include <algorithm>
#include <cstdint>
#include <functional>
#include <utility>
#include <vector>




using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;




inline static constexpr auto max2 =
    []<typename T> [[gnu::always_inline]] (const T& a, const T& b) -> const T&
{
    return std::max(a, b);
};


inline static constexpr auto upd =
    []<typename T, typename F> [[gnu::always_inline]] (
        T & x,
        const std::type_identity_t<T>& another,
        F&& f) -> T&
{
    return x = std::forward<F>(f)(x, another);
};

inline static constexpr auto upd_max =
    std::bind(upd, std::placeholders::_1, std::placeholders::_2, max2);




inline static constexpr auto min2 =
    []<typename T> [[gnu::always_inline]] (const T& a, const T& b) -> const T&
{
    return std::min(a, b);
};

inline static constexpr auto upd_min =
    std::bind(upd, std::placeholders::_1, std::placeholders::_2, min2);

class Solution
{
public:
    [[nodiscard]] int findMaxVal(
        u32 n,
        std::vector<std::vector<int>>& rstr,
        const std::vector<int>& diff) noexcept
    {
        static int hi[100001];
        std::fill_n(hi, n, 10'000'000);
        hi[0] = 0;
        for (auto& x : rstr) hi[x[0]] = x[1];

        for (u32 i = 1; i != n; ++i)
        {
            auto& curr_hi = hi[i];
            upd_min(curr_hi, hi[i - 1] + diff[i - 1]);
        }

        int next_hi = hi[n - 1], mv = next_hi;
        for (u32 i = n - 2; i; --i)
        {
            upd_min(next_hi += diff[i], hi[i]);
            upd_max(mv, next_hi);
        }
        return mv;
    }
};
