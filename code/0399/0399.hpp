#include <optional>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

class Solution
{
public:
    std::vector<double> calcEquation(
        const std::vector<std::vector<std::string>>& equations,
        const std::vector<double>& values,
        const std::vector<std::vector<std::string>>& queries)
    {
        std::unordered_map<std::string, size_t> registry;
        auto reg = [&](const std::string& s)
        {
            size_t prev_size = registry.size();
            auto& id = registry[s];
            if (registry.size() != prev_size)
            {
                id = prev_size;
            }
            return id;
        };

        std::optional<double> value[40][40];

        for (auto [e, v] : std::views::zip(equations, values))
        {
            auto i = reg(e[0]);
            auto j = reg(e[1]);
            value[i][j] = v;
            value[j][i] = 1.0 / v;
        }

        const auto n = registry.size();

        for (size_t k = 0; k != n; ++k)
        {
            for (size_t i = 0; i != n; ++i)
            {
                for (size_t j = 0; j != n; ++j)
                {
                    if (!value[i][j] && value[i][k] && value[k][j])
                    {
                        value[i][j] = *value[i][k] * *value[k][j];
                    }
                }
            }
        }

        auto query = [&](auto& q)
        {
            auto it_i = registry.find(q[0]);
            auto it_j = registry.find(q[1]);
            auto end = registry.end();
            if (it_i != end && it_j != end)
            {
                return value[it_i->second][it_j->second].value_or(-1.0);
            }
            return -1.0;
        };
        return queries | std::views::transform(query) |
               std::ranges::to<std::vector>();
    }
};
