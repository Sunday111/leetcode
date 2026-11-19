#include <numeric>
#include <string>

class Solution
{
public:
    [[nodiscard]] static constexpr std::string gcdOfStrings(
        std::string_view a,
        std::string_view b) noexcept
    {
        if (a.size() > b.size()) std::swap(a, b);
        const size_t la = a.size(), lb = b.size();
        size_t l = 0;
        if (b.starts_with(a) && b.ends_with(a) &&
            b.substr(la) == b.substr(0, lb - la))
        {
            l = std::gcd(la, lb);
        }

        return std::string(a.substr(0, l));
    }
};
