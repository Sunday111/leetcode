#include <cassert>
#include <span>
#include <string_view>
#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    using u16 = uint16_t;
    using u64 = uint64_t;

    struct Entry
    {
        constexpr bool is_empty() const noexcept { return l == 0; }
        constexpr void push(u8 v) noexcept
        {
            u8 shift = l++ * 4u;
            values &= ~(0b1111ul << shift);
            values |= (u64{v} << shift);
        }
        [[nodiscard]] constexpr u8 pop() noexcept
        {
            u8 shift = --l * 4u;
            return (values >> shift) & 0b1111ul;
        }

        u64 values : 60;
        u64 l : 4;
    };

    inline static std::array<Entry, 1 << 15> dp_data;

    [[nodiscard]] static std::vector<std::vector<std::string>> partition(
        std::string_view s) noexcept
    {
        const u8 n = s.size() & 0xFF;

        u16 dp_data_dize = 0;
        dp_data[dp_data_dize++].l = 0;
        std::array<std::span<const Entry>, 17> dp;
        dp[n] = std::span{dp_data}.first(1);

        auto isPalindrome = [&](u8 first, u8 last)
        {
            while (first < last)
            {
                if (s[first] != s[last]) return false;
                ++first, --last;
            }

            return true;
        };

        for (u8 i = n - 1; i != 0; --i)
        {
            auto offset = dp_data_dize;
            for (u8 j = i; j != n; ++j)
            {
                if (isPalindrome(i, j))
                {
                    for (auto e : dp[j + 1])
                    {
                        e.push(i);
                        dp_data[dp_data_dize++] = e;
                    }
                }
            }
            dp[i] = std::span{dp_data}.first(dp_data_dize).subspan(offset);
        }

        std::vector<std::vector<std::string>> ans;
        ans.reserve(1 << (n - 1));

        for (u8 j = 0; j != n; ++j)
        {
            if (isPalindrome(0, j))
            {
                for (auto e : dp[j + 1])
                {
                    auto& x = ans.emplace_back();
                    x.reserve(e.l + 1);

                    u8 prev = 0;
                    while (!e.is_empty())
                    {
                        auto curr = e.pop();
                        x.emplace_back(s.substr(prev, curr - prev));
                        prev = curr;
                    }
                    x.emplace_back(s.substr(prev));
                }
            }
        }

        return ans;
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
