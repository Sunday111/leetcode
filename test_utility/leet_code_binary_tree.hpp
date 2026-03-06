#pragma once

#include <algorithm>
#include <cassert>
#include <format>
#include <optional>
#include <queue>
#include <span>
#include <sstream>
#include <unordered_set>

#include "cast.hpp"
#include "convert_expected_type.hpp"
#include "scan.hpp"

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
    std::queue<std::pair<TNode*, TNode*>> q;
    q.emplace(root_a, root_b);

    while (!q.empty())
    {
        auto [a, b] = q.front();
        q.pop();

        if (cast<bool>(a) ^ cast<bool>(b)) return false;
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
    using NodeType = TNode;
    using NodeValue = std::decay_t<decltype(TNode{}.val)>;
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
                std::next(queue.begin(), cast<int64_t>(k)));
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

    [[nodiscard]] constexpr static auto ToArray(TNode* root) noexcept
    {
        std::vector<std::optional<NodeValue>> r;

        std::vector<TNode*> q;
        q.push_back(root);

        // BFS
        size_t begin = 0;
        while (begin < q.size())
        {
            size_t end = q.size();
            for (size_t i = begin; i != end; ++i)
            {
                auto& v = r.emplace_back();
                auto node = q[i];
                if (node)
                {
                    v = node->val;
                    q.emplace_back(node->left);
                    q.emplace_back(node->right);
                }
            }

            begin = end;
        }

        while (r.size() && !r.back()) r.pop_back();

        return r;
    }

    [[nodiscard]] constexpr static auto ToString(
        const std::vector<std::optional<NodeValue>> a) noexcept
    {
        std::string r;

        r += '[';

        for (size_t i = 0; i != a.size(); ++i)
        {
            if (i) r += ',';
            auto& v = a[i];
            if (v)
            {
                std::format_to(std::back_inserter(r), "{}", *v);
            }
            else
            {
                r += "null";
            }
        }

        r += ']';

        return r;
    }

    [[nodiscard]] constexpr static auto ToString(TNode* root) noexcept
    {
        auto a = ToArray(root);
        return ToString(a);
    }
};

template <BinaryTreeNodeConcept TNode>
void DeleteBinaryTree(TNode* node)
{
    if (node)
    {
        DeleteBinaryTree(node->left);
        DeleteBinaryTree(node->right);
        delete node;  // NOLINT
    }
}

template <BinaryTreeNodeConcept TNode>
void DeleteBinaryTreesWithSharedNodes(std::span<TNode*> nodes)
{
    std::unordered_set<TNode*> deleted;

    auto dfs = [&](this auto&& dfs, TNode* x) -> void
    {
        if (!x || !deleted.emplace(x).second) return;
        auto l = x->left, r = x->right;
        delete x;  // NOLINT
        dfs(l);
        dfs(r);
    };

    std::ranges::for_each(nodes, dfs);
}

template <BinaryTreeNodeConcept Node>
struct ConvertExpectedType<Node*, void>
{
    using Result = LeetCodeBinaryTree<Node>;
};

template <typename Options, is_specialization<LeetCodeBinaryTree> T>
[[nodiscard]] constexpr size_t
do_scan(const Options& opts, std::string_view s, size_t start, T& r)
{
    using NodeType = T::NodeType;
    using ValueType = decltype(NodeType{}.val);
    using Elem = std::optional<ValueType>;
    std::vector<Elem> vals;
    size_t i = do_scan(opts, s, start, vals);
    r = T::FromArray(vals);
    return i;
}
