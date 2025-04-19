#pragma once

#include <cassert>
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

        auto handle_node = [&](TreeNode* node)
        {
            s << node->val;

            switch (static_cast<int>(node->left != nullptr) << 1 |
                    static_cast<int>(node->right != nullptr))
            {
            case 0b00:
                s << 'n';
                break;

            case 0b01:
                s << 'r';
                queue.push(node->right);
                break;

            case 0b10:
                s << 'l';
                queue.push(node->left);
                break;

            case 0b11:
                s << 'b';
                queue.push(node->left);
                queue.push(node->right);
                break;
            }
        };

        handle_node(root);

        while (!queue.empty())
        {
            s << ',';
            handle_node(queue.front());
            queue.pop();
        }

        return std::move(s).str();
    }

    // Decodes your encoded data to tree.
    static TreeNode* deserialize(std::string_view data)
    {
        if (data.empty()) return nullptr;

        std::queue<std::pair<TreeNode*, char>> queue;
        size_t i = 0;

        auto read_number = [&]() -> std::pair<int, char>
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

            return {negative ? -value : value, data[i++]};
        };

        auto enqueue = [&](TreeNode* node, char c)
        {
            if (c != 'n') queue.emplace(node, c);
        };

        auto [root_value, root_c] = read_number();
        TreeNode* root = new TreeNode(root_value);  // NOLINT
        enqueue(root, root_c);

        while (!queue.empty())
        {
            assert(data[i] == ',');
            ++i;

            auto [parent, parent_c] = queue.front();
            queue.pop();

            switch (parent_c)
            {
            case 'l':
            {
                auto [v, c] = read_number();
                parent->left = new TreeNode(v);  // NOLINT
                enqueue(parent->left, c);
                break;
            }
            case 'r':
            {
                auto [v, c] = read_number();
                parent->right = new TreeNode(v);  // NOLINT
                enqueue(parent->right, c);
                break;
            }
            case 'b':
            {
                {
                    auto [v, c] = read_number();
                    parent->left = new TreeNode(v);  // NOLINT
                    enqueue(parent->left, c);
                }
                assert(data[i] == ',');
                ++i;
                {
                    auto [v, c] = read_number();
                    parent->right = new TreeNode(v);  // NOLINT
                    enqueue(parent->right, c);
                }
                break;
            }
            }
        }

        return root;
    }
};
