#include <cassert>
#include <optional>
#include <queue>
#include <span>
#include <sstream>

template <typename T>
concept BinaryTreeNodeConcept = requires(T a, int x) {
    // Has left and right properties convertible to pointers of the same type
    { a.left } -> std::convertible_to<T*>;
    { a.right } -> std::convertible_to<T*>;

    // Has integral val property
    requires std::integral<std::remove_cvref_t<decltype(a.val)>>;

    // constructible from integral
    T{x};
};

template <BinaryTreeNodeConcept TNode>
bool CompareBinaryTrees(TNode* root_a, TNode* root_b)
{
    std::queue<std::pair<TNode*, TNode*>> q{{root_a, root_b}};

    while (!q.empty())
    {
        auto [a, b] = q.front();
        q.pop();

        if (static_cast<bool>(a) ^ static_cast<bool>(b)) return false;
        if (!a) continue;
        if (a->val != b->val) return false;

        q.emplace(a->left, b->left);
        q.emplace(a->right, b->right);
    }

    return true;
}

template <BinaryTreeNodeConcept TNode>
struct LeetCodeBinaryTree
{
    std::deque<TNode> nodes;
    TNode* root = nullptr;

    [[nodiscard]] TNode* AllocNode(int value)
    {
        nodes.emplace_back(value);
        return &nodes.back();
    }

    [[nodiscard]] static LeetCodeBinaryTree FromArray(
        std::span<std::optional<int>> values)
    {
        LeetCodeBinaryTree<TNode> tree;

        if (!values.front()) return tree;

        tree.root = tree.AllocNode(*values.front());

        std::vector<TNode*> queue{tree.root};
        size_t next_value_index = 1;

        auto try_assign_and_enqueue_child = [&](TNode*& child)
        {
            if (auto& opt = values[next_value_index])
            {
                child = tree.AllocNode(*opt);
                queue.push_back(child);
            }
        };

        while (next_value_index < values.size())
        {
            // The number of nodes at the current tree depth
            size_t k = queue.size();

            for (size_t i = 0; i != k && next_value_index < values.size(); ++i)
            {
                auto node = queue[i];
                try_assign_and_enqueue_child(node->left);
                ++next_value_index;

                if (next_value_index < values.size())
                {
                    try_assign_and_enqueue_child(node->right);
                }

                ++next_value_index;
            }

            // Erase k handled nodes from the beginning of the queue
            queue.erase(
                queue.begin(),
                std::next(queue.begin(), static_cast<int64_t>(k)));
        }

        return tree;
    }

    [[nodiscard]] static std::vector<std::optional<int>> StringToArray(
        std::string_view str)
    {
        std::stringstream stream(std::string{str});
        std::vector<std::optional<int>> r;

        while (!stream.eof())
        {
            if (int c = stream.peek(); std::isdigit(c) || c == '-')
            {
                int value{};
                stream >> value;
                r.push_back(value);
            }
            else
            {
                [[maybe_unused]] int c0 = stream.get();
                [[maybe_unused]] int c1 = stream.get();
                [[maybe_unused]] int c2 = stream.get();
                [[maybe_unused]] int c3 = stream.get();

                assert(c0 == 'n');
                assert(c1 == 'u');
                assert(c2 == 'l');
                assert(c3 == 'l');

                r.push_back(std::nullopt);
            }

            if (int p = stream.peek(); p == ',') stream.get();
        }

        return r;
    }

    [[nodiscard]] static LeetCodeBinaryTree FromString(std::string_view str)
    {
        auto array = StringToArray(str);
        return FromArray(array);
    }
};
