#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<int> pivotArray(
        const std::vector<int>& nums,
        int pivot) noexcept
    {
        size_t i = 0, n = nums.size(), j = n;
        std::vector<int> r;
        r.resize(n);

        for (int v : nums)
        {
            r[i] = v;
            r[j - 1] = v;
            i += v < pivot;
            j -= v > pivot;
        }

        // write pivot values between i and j
        while (i != j) r[i++] = pivot;
        // reverse values greater than pivot
        // because they were visited in reverse order
        for (j = n - 1; i < j; ++i, --j) std::swap(r[i], r[j]);

        return r;
    }
};
