#include <concepts>
#include <ranges>
#include <type_traits>
#include <vector>




inline static constexpr auto iif =
    []<std::integral T> [[nodiscard, gnu::always_inline]] (
        bool c,
        T a,
        std::type_identity_t<T> b) noexcept -> T
{
    return b ^ ((a ^ b) & static_cast<T>(-c));
};
#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

using u32 = uint32_t;
namespace stdr = std::ranges;
namespace stdv = std::views;
class Solution
{
public:
    std::vector<bool> pathExistenceQueries(
        const u32 n,
        std::vector<int>& nums,
        const int md,
        const std::vector<std::vector<int>>& queries) noexcept
    {
        auto p = reinterpret_cast<u32*>(nums.data());
        int vj = nums[0];
        p[0] = 0;
        for (u32 i = 1; i != n; ++i)
        {
            int vi = nums[i];
            p[i] = iif(vi - vj <= md, p[i - 1], i);
            vj = vi;
        }
        auto query = [&] [[gnu::always_inline]] (const std::vector<int>& q)
        {
            return p[q[0]] == p[q[1]];
        };
        return queries | stdv::transform(query) | stdr::to<std::vector>();
    }
};
