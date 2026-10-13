#include <ranges>
#include <string>

#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

class Solution
{
public:
    std::string maxSumOfSquares(size_t n, size_t s) const noexcept
    {
        if (n * 9 < s) return {};

        size_t q = s / 9;
        size_t rem = s % 9;
        bool fill_nines = q <= n - q - !!rem;
        std::string ans(n, fill_nines ? '0' : '9');
        if (fill_nines)
        {
            std::ranges::fill(ans | std::views::take(q), '9');
        }
        else
        {
            std::ranges::fill(ans | std::views::drop(q + !!rem), '0');
        }
        if (rem)
        {
            ans[q] = static_cast<char>('0' + rem);
        }
        return ans;
    }
};
