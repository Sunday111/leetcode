#pragma once

#include <algorithm>
#include <unordered_map>
#include <vector>

struct TreeNode
{
    int val;
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};
    explicit TreeNode(int x) : val(x) {}
};

class Solution
{
public:
    [[nodiscard]] static constexpr std::vector<std::vector<int>>
    verticalTraversal(TreeNode* root) noexcept
    {
        std::vector<std::pair<TreeNode*, int>> q;
        std::unordered_map<int, std::vector<std::pair<int, int>>>
            column_to_values;
        size_t front = 0;
        int min_column = 1, max_column = -1;
        if (root) q.emplace_back(root, 0);

        for (int row = 0; front != q.size(); ++row)
        {
            size_t row_end = q.size();
            while (front != row_end)
            {
                auto [node, column] = q[front++];
                column_to_values[column].emplace_back(node->val, row);
                if (column < min_column) min_column = column;
                if (column > max_column) max_column = column;
                if (node->left) q.emplace_back(node->left, column - 1);
                if (node->right) q.emplace_back(node->right, column + 1);
            }

            front = row_end;
        }

        std::vector<std::vector<int>> r;
        r.reserve(column_to_values.size());
        for (int column = min_column; column <= max_column; ++column)
        {
            auto& values_and_rows = column_to_values[column];
            std::ranges::sort(
                values_and_rows,
                [](const std::pair<int, int>& a, const std::pair<int, int>& b)
                {
                    if (a.second == b.second) return a.first < b.first;
                    return a.second < b.second;
                });
            auto& values = r.emplace_back();
            values.reserve(values_and_rows.size());
            for (auto& [val, row] : values_and_rows) values.push_back(val);
        }

        return r;
    }
};
