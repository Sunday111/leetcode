#include <cassert>
#include <queue>
#include <sstream>

#include "lc_tree_node.hpp"

class Codec
{
public:
    template <typename E, typename C>
    [[nodiscard]] static E queuePop(std::queue<E, C>& q)
    {
        auto value = q.front();
        q.pop();
        return value;
    }

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
            handle_node(queuePop(queue));
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

        auto make_node_and_enqueue = [&]()
        {
            auto [value, c] = read_number();
            TreeNode* node = new TreeNode(value);  // NOLINT
            if (c != 'n') queue.emplace(node, c);
            return node;
        };

        auto skip_comma = [&]()
        {
            assert(data[i] == ',');
            ++i;
        };

        TreeNode* root = make_node_and_enqueue();

        while (!queue.empty())
        {
            skip_comma();

            auto [parent, parent_c] = queuePop(queue);

            switch (parent_c)
            {
            case 'l':
                parent->left = make_node_and_enqueue();
                break;

            case 'r':
                parent->right = make_node_and_enqueue();
                break;

            case 'b':
                parent->left = make_node_and_enqueue();
                skip_comma();
                parent->right = make_node_and_enqueue();
                break;
            }
        }

        return root;
    }
};
