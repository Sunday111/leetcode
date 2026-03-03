#include <span>
#include <vector>



#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

class Solution
{
    [[nodiscard]] std::vector<std::vector<int>> impl(
        const std::span<const int> nums) noexcept
    {
        if (nums.empty()) return {{}};
        auto r = impl(nums.last(nums.size() - 1));
        const auto n = r.size();
        r.reserve(n * 2);
        r.insert(r.end(), r.begin(), r.end());
        for (size_t i = 0; i != n; ++i) r[i].push_back(nums.front());
        return r;
    }

public:
    [[nodiscard]] FORCE_INLINE std::vector<std::vector<int>> subsets(
        std::vector<int>& nums) noexcept
    {
        return impl(std::span{nums});
    }
};
