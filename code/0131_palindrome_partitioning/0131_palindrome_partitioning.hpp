#include <cassert>
#include <span>
#include <string_view>
#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    std::string_view s;

    struct Entry
    {
        u8 push(u8 v) noexcept { return values[l++] = v; }
        u8 pop() noexcept { return values[--l]; }

        std::array<u8, 15> values{};
        u8 l = 0;
    };

    u8 n{};

    [[nodiscard]] constexpr bool isPalindrome(u8 first, u8 last) noexcept
    {
        while (first < last)
        {
            if (s[first] != s[last]) return false;
            ++first, --last;
        }

        return true;
    }

    std::vector<std::vector<std::string>> results;
    // std::array<std::span<const Entry>, 16> memo;
    Entry current;

    static std::vector<std::string> to_vector(
        Entry e,
        std::string_view s) noexcept
    {
        std::vector<std::string> x;
        x.reserve(e.l);

        u8 prev = 0;
        for (u8 i = 0; i != e.l; ++i)
        {
            u8 curr = e.values[i];
            x.emplace_back(s.substr(prev, curr - prev));
            prev = curr;
        }

        return x;
    }

    constexpr void dfs(u8 start) noexcept
    {
        if (start == n)
        {
            results.emplace_back(to_vector(current, s));
        }
        else
        {
            for (u8 last = start; last != n; ++last)
            {
                if (isPalindrome(start, last))
                {
                    dfs(current.push(last + 1));
                    current.pop();
                }
            }
        }
    }

    [[nodiscard]] std::vector<std::vector<std::string>> partition(
        std::string_view s_) noexcept
    {
        s = s_;
        n = s.size() & 0xFF;
        results.reserve(1u << (n - 1));
        dfs(0);
        return std::move(results);
    }
};
