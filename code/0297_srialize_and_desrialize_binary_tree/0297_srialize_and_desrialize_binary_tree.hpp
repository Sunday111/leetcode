#pragma once

#include <cassert>
#include <optional>
#include <queue>
#include <sstream>

struct TreeNode
{
    int val;
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};
    explicit TreeNode(int x) : val(x) {}
};

class Codec
{
public:
    // Encodes a tree to a single string.
    static std::string serialize(TreeNode* root)
    {
        if (!root) return "";

        std::queue<TreeNode*> queue;
        std::stringstream s;
        s << root->val;

        queue.push(root);

        size_t none_counter = 0;

        auto write_node = [&](TreeNode* node)
        {
            if (node)
            {
                if (none_counter)
                {
                    s << ',';
                    s << none_counter;
                    s << 'x';
                    none_counter = 0;
                }

                s << ',';
                s << node->val;
            }
            else
            {
                ++none_counter;
            }
        };

        while (!queue.empty())
        {
            auto node = queue.front();
            queue.pop();

            write_node(node->left);
            if (node->left) queue.push(node->left);

            write_node(node->right);
            if (node->right) queue.push(node->right);
        }

        return std::move(s).str();
    }

    // Decodes your encoded data to tree.
    static TreeNode* deserialize(std::string_view data)
    {
        if (data.empty()) return nullptr;

        std::queue<TreeNode*> queue;
        size_t i = 0;

        auto read_number = [&]()
        {
            int value = 0;

            const bool negative = [&]
            {
                if (data[i] != '-') return false;

                ++i;
                return true;
            }();

            assert(std::isdigit(data[i]));

            do
            {
                value = value * 10 + (data[i++] - '0');
            } while (i < data.size() && std::isdigit(data[i]));

            return negative ? -value : value;
        };

        std::optional<size_t> current_none_block;

        auto read_node_value = [&]() -> std::optional<int>
        {
            if (current_none_block)
            {
                size_t& count = *current_none_block;
                assert(count > 0);
                if (--count == 0)
                {
                    current_none_block = std::nullopt;
                }
                return std::nullopt;
            }

            if (i >= data.size()) return std::nullopt;

            assert(data[i] == ',');
            i++;

            int value = read_number();

            if (i < data.size() && data[i] == 'x')
            {
                ++i;
                assert(value > 0);
                if (--value)
                {
                    current_none_block = value;
                }

                return std::nullopt;
            }
            else
            {
                return value;
            }
        };

        TreeNode* root = new TreeNode(read_number());  // NOLINT

        queue.push(root);

        while (i < data.size())
        {
            auto node = queue.front();
            queue.pop();

            if (auto opt = read_node_value())
            {
                node->left = new TreeNode(*opt);  // NOLINT
                queue.push(node->left);
            }

            if (auto opt = read_node_value())
            {
                node->right = new TreeNode(*opt);  // NOLINT
                queue.push(node->right);
            }
        }

        return root;
    }
};
