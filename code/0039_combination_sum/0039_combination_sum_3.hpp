#include <bit>
#include <unordered_map>
#include <vector>

class Solution3
{
public:
    uint64_t candidates;
    std::unordered_map<uint16_t, std::vector<std::string>> memo;

    std::vector<std::vector<int>> combinationSum(
        std::vector<int>& candidates_,
        int target)
    {
        candidates = 0;
        for (auto x : candidates_) candidates |= uint64_t{1} << x;

        memo.clear();
        memo.reserve(40);
        auto bitsets = dfs(static_cast<uint8_t>(target), 0);

        std::vector<std::vector<int>> result;
        result.reserve(bitsets.size());

        for (auto& result_s : bitsets)
        {
            auto& result_i = result.emplace_back();
            result_i.reserve(result_s.size());
            for (auto v : result_s) result_i.push_back(v);
        }

        return result;
    }

    std::vector<std::string> dfs(uint8_t target, uint8_t start)
    {
        if (target == 0) return {{}};

        uint16_t key = static_cast<uint16_t>((int{target} << 8) | int{start});
        if (auto it = memo.find(key); it != memo.end())
        {
            return it->second;
        }

        std::vector<std::string> result;

        uint64_t local_candidates = candidates;
        uint64_t mask = std::numeric_limits<uint64_t>::max();
        mask <<= start;
        local_candidates &= mask;

        char c = 0;
        do
        {
            c = static_cast<char>(std::countr_zero(local_candidates));
            mask = 1 << c;
            local_candidates &= ~mask;
            if (c > target) break;
            auto sub =
                dfs(static_cast<uint8_t>(target - c),
                    std::bit_cast<uint8_t>(c));
            for (auto& s : sub)
            {
                s.push_back(c);
                result.push_back(std::move(s));
            }
        } while (c != (sizeof(local_candidates) * 8));

        return memo[key] = std::move(result);
    }
};
