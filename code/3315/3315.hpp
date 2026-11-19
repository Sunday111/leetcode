#include <vector>

class Solution {
public:
    [[nodiscard]] static constexpr auto minBitwiseArray(std::vector<int>& nums) noexcept {
        for (int& n : nums) {
            n = (n & ~(((n + 1) & ~n) >> 1)) | ((n & 1) - 1);
        }
        return std::move(nums);
    }
};
