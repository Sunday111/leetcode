#include <algorithm>
#include <vector>
class Solution
{
public:
    std::vector<std::vector<int>> intervalIntersection(
        std::vector<std::vector<int>>& l1,
        std::vector<std::vector<int>>& l2) const noexcept
    {
        if (l2.size() > l1.size()) std::swap(l1, l2);

        std::vector<int>* buf[2]{l1.data(), l2.data()};

        size_t i[2]{}, o[2]{};
        const size_t n[2]{l1.size(), l2.size()};

        while ((i[0] != n[0]) & (i[1] != n[1]))
        {
            auto& a = l1[i[0]];
            auto& b = l2[i[1]];

            bool take1 = a[1] > b[1];
            auto& out = buf[take1][o[take1]];
            out[0] = std::max(a[0], b[0]);
            out[1] = std::min(a[1], b[1]);

            ++i[take1];
            o[take1] += out[0] <= out[1];
        }

        l1.resize(o[0] + o[1]);
        buf[0] = l1.data();

        // Merge backwards.
        size_t k = l1.size();
        while (o[0] && o[1])
        {
            bool take1 = l1[o[0] - 1][0] <= l2[o[1] - 1][0];
            l1[--k] = std::move(buf[take1][--o[take1]]);
        }

        // Append tail
        std::ranges::move(buf[1], buf[1] + o[1], buf[0]);

        return std::move(l1);
    }
};
