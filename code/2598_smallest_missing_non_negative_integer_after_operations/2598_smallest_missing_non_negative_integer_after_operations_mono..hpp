#include <concepts>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

#define HOT_PATH __attribute__((hot))

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & static_cast<T>(-c)) + (b & static_cast<T>(~static_cast<T>(-c)));
}

int mod[100000];  // NOLINT
class Solution
{
public:
    static int findSmallestInteger(std::vector<int>& nums, int value) noexcept
    {
        const int n = static_cast<int>(nums.size());
        std::fill_n(mod, value, 0);
        for (int x : nums)
        {
            x %= value;
            x += iif(x < 0, value, 0);
            ++mod[x];
        }
        for (int i = 0; i != n; ++i)
        {
            if (!(mod[i % value]--))
            {
                return i;
            }
        }
        return n;
    }
};

#ifndef __clang__
auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
#endif
