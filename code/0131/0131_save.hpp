#include <cassert>
#include <string_view>
#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    std::string_view s;
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
    std::vector<std::string> current;

    constexpr void dfs(u8 start) noexcept
    {
        if (start == n)
        {
            results.push_back(current);
            return;
        }

        for (u8 last = start; last != n; ++last)
        {
            if (isPalindrome(start, last))
            {
                current.emplace_back(s.substr(start, last - start + 1));
                dfs(last + 1);
                current.pop_back();
            }
        }
    }

    [[nodiscard]] std::vector<std::vector<std::string>> partition(
        std::string_view s_) noexcept
    {
        s = s_;
        n = s.size() & 0xFF;
        dfs(0);
        return std::move(results);
    }
};
