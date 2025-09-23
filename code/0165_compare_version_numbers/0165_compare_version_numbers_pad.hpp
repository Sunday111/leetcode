#include <algorithm>
#include <ranges>
#include <string_view>
#include <vector>

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
        return std::ranges::to<std::vector>(
            std::views::split(str, '.') | std::views::transform(toInt));
    }

    [[nodiscard]] static constexpr int compareVersion(
        std::string_view version1,
        std::string_view version2) noexcept
    {
        auto nums1 = toNumbers(version1), nums2 = toNumbers(version2);
        size_t max_size = std::max(nums1.size(), nums2.size());
        nums1.resize(max_size, 0);
        nums2.resize(max_size, 0);
        const std::strong_ordering cmp = nums1 <=> nums2;
        if (cmp == std::strong_ordering::less) return -1;
        if (cmp == std::strong_ordering::greater) return 1;
        return 0;
    }
};
