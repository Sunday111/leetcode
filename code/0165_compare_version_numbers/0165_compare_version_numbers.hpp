#include <ranges>
#include <string_view>

class Solution
{
public:
    static constexpr auto toInt = []<typename Range>(Range&& range)
    {
        int v = 0;
        for (char c : std::forward<Range>(range)) v = v * 10 + (c - '0');
        return v;
    };

    [[nodiscard]] static constexpr auto toNumbers(std::string_view str) noexcept
    {
        return std::views::split(str, '.') | std::views::transform(toInt);
    }

    [[nodiscard]] static constexpr int compareVersion(
        std::string_view version1,
        std::string_view version2) noexcept
    {
        auto nums1 = toNumbers(version1), nums2 = toNumbers(version2);
        auto it1 = nums1.begin(), it2 = nums2.begin();
        auto e1 = nums1.end(), e2 = nums2.end();
        while (it1 != e1 || it2 != e2)
        {
            int v1 = it1 != e1 ? *it1++ : 0;
            int v2 = it2 != e2 ? *it2++ : 0;
            if (v1 != v2) return v1 < v2 ? -1 : 1;
        }

        return 0;
    }
};
