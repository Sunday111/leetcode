#include <algorithm>
#include <span>
#include <unordered_map>
#include <vector>

class Solution2
{
public:
    std::span<const int> candidates;
    std::unordered_map<int, std::vector<std::vector<int>>> memo;

    std::vector<std::vector<int>> combinationSum(
        std::vector<int>& candidates_,
        int target)
    {
        std::ranges::sort(candidates_);
        candidates = candidates_;
        memo.clear();
        memo.reserve(40);
        return dfs(target, 0);
    }

    std::vector<std::vector<int>> dfs(int target, size_t start)
    {
        if (target == 0) return {{}};

        int key = target * 31 + static_cast<int>(start);
        if (auto it = memo.find(key); it != memo.end())
        {
            return it->second;
        }

        std::vector<std::vector<int>> result;
        for (size_t i = start; i != candidates.size(); ++i)
        {
            int c = candidates[i];
            if (c > target) break;
            auto sub = dfs(target - c, i);
            for (auto& s : sub)
            {
                s.insert(s.begin(), c);
                result.push_back(std::move(s));
            }
        }

        return memo[key] = std::move(result);
    }
};
