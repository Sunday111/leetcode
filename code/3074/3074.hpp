#include <algorithm>
#include <numeric>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int minimumBoxes(
        std::vector<int>& apple,
        std::vector<int>& capacity) noexcept
    {
        int s = std::accumulate(apple.begin(), apple.end(), 0);
        std::ranges::sort(capacity, std::greater{});
        int r = 0;
        for (int v : capacity)
        {
            if (s < 1) break;
            s -= v;
            ++r;
        }
        return r;
    }
};
