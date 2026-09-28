#include <cctype>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution
{
public:
    using Op = int (*)(int, int);
    static Op get_op(char c)
    {
        switch (c)
        {
        case '+':
            return [](int a, int b)
            {
                return a + b;
            };
        case '-':
            return [](int a, int b)
            {
                return a - b;
            };
        case '*':
            return [](int a, int b)
            {
                return a * b;
            };
        }
        std::unreachable();
    }

    std::string_view e;
    std::unordered_map<size_t, std::vector<int>> memo;
    std::vector<int> diffWaysToCompute(std::string_view expression)
    {
        e = expression;
        return dfs(0, e.size());
    }

    std::vector<int> dfs(size_t begin, size_t end)
    {
        auto& ans = memo[(begin << 8) | end];
        if (ans.empty())
        {
            for (size_t i = begin; i != end; ++i)
            {
                if (std::isdigit(e[i])) continue;

                auto op = get_op(e[i]);
                auto left = dfs(begin, i);
                auto right = dfs(i + 1, end);

                ans.reserve(ans.size() + left.size() * right.size());
                for (int l : left)
                {
                    for (int r : right)
                    {
                        ans.push_back(op(l, r));
                    }
                }
            }
        }

        if (ans.empty())
        {
            size_t i = begin;
            int v = e[i++] - '0';
            if (i != end && std::isdigit(e[i]))
            {
                v = v * 10 + e[i] - '0';
            }
            ans = {v};
        }
        return ans;
    }
};
