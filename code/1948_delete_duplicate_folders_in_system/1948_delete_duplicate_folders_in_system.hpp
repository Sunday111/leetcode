#pragma once

#include <algorithm>
#include <deque>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

#define DEBUG_PRINT

#ifdef DEBUG_PRINT
#include <chrono>
#include <print>
#endif

#ifdef __GNUC__
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#define FORCE_INLINE inline
#endif

using u32 = uint32_t;

struct Node
{
    std::string_view name;
    Node* child{};
    Node* sibling{};
    size_t content_hash = 0;
    bool duplicate = false;
};

class Solution
{
public:
#ifdef DEBUG_PRINT
    FORCE_INLINE void print_node(u32 depth, Node* node)
    {
        std::print("{:{}} '{}'", "", depth * 4, node->name);

        if (node->duplicate) std::print(" DUPLICATE");

        std::println();

        u32 next_depth = depth + 1;
        for (auto child = node->child; child; child = child->sibling)
        {
            print_node(next_depth, child);
        }
    }
#endif

    [[nodiscard]] FORCE_INLINE static constexpr size_t hash_combine(
        size_t a,
        size_t b) noexcept
    {
        // return a ^ b;
        return a ^ (b + 0x9e3779b9 + (a << 6) + (a >> 2));
    }

    FORCE_INLINE static constexpr void hash_combine_inplace(
        size_t& a,
        size_t b) noexcept
    {
        a = a ^ (b + 0x9e3779b9 + (a << 6) + (a >> 2));
    }

    [[nodiscard]] FORCE_INLINE size_t hash_node(Node* node) noexcept
    {
        for (Node* child = node->child; child; child = child->sibling)
        {
            hash_combine_inplace(node->content_hash, hash_node(child));
        }

        size_t name_hash = std::hash<std::string_view>{}(node->name);
        return hash_combine(node->content_hash, name_hash);
    }

    constexpr void deleteDuplicates(Node* node) noexcept
    {
        lookup.reserve(nodes.size());

        {
            if (!node->child) return;
            if (node->duplicate) return;

            auto [it, inserted] = lookup.insert(node);
            if (!inserted)
            {
                node->duplicate = true;
                (*it)->duplicate = true;
            }

            node = node->child;
        }

        while (node)
        {
            deleteDuplicates(node);
            node = node->sibling;
        }
    }

    constexpr void buildResult(Node* node) noexcept
    {
        {
            if (node->duplicate) return;
            tmp_path.emplace_back(node->name);
            result.push_back(tmp_path);
            node = node->child;
        }

        while (node)
        {
            buildResult(node);
            node = node->sibling;
        }

        tmp_path.pop_back();
    }

    constexpr std::vector<std::vector<std::string>> deleteDuplicateFolder(
        std::vector<std::vector<std::string>>& paths) noexcept
    {
#ifdef DEBUG_PRINT
        auto t0 = std::chrono::high_resolution_clock::now();
#endif
        std::ranges::sort(paths);

        nodes.push_back({
            .name = "",
        });

        Node* root = &nodes.front();
        for (auto& path : paths)
        {
            Node* parent = root;

            for (auto& dir_name : path)
            {
                auto node = parent->child;

                if (!node || node->name != dir_name)
                {
                    nodes.push_back({
                        .name = dir_name,
                        .child = nullptr,
                        .sibling = node,
                    });
                    node = &nodes.back();
                    parent->child = node;
                }

                parent = node;
            }
        }

        [[maybe_unused]] auto root_hash = hash_node(root);

        deleteDuplicates(root);

#ifdef DEBUG_PRINT
        print_node(0, root);
#endif

        for (auto node = root->child; node; node = node->sibling)
        {
            buildResult(node);
        }

#ifdef DEBUG_PRINT
        auto t1 = std::chrono::high_resolution_clock::now();
        auto dur =
            std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
        std::println("Duration: {}", dur);
        std::println("Results:");
        for (auto& path : result)
        {
            std::print("    ");
            for (auto& dir_name : path)
            {
                std::print("{} ", dir_name);
            }
            std::println("");
        }
#endif

        return result;
    }

    template <bool with_names>
    [[nodiscard]] static constexpr bool nodesEq(Node* a, Node* b) noexcept
    {
        if (a->content_hash != b->content_hash) return false;
        if constexpr (with_names)
        {
            if (a->name != b->name) return false;
        }
        a = a->child;
        b = b->child;

        while (a && b && nodesEq<true>(a, b))
        {
            a = a->sibling;
            b = b->sibling;
        }

        return a == b;
    }

    struct LookupHasher
    {
        [[nodiscard]] FORCE_INLINE constexpr size_t operator()(
            Node* node) const noexcept
        {
            return node->content_hash;
        }
    };

    struct LookupComparator
    {
        [[nodiscard]] FORCE_INLINE constexpr size_t operator()(Node* a, Node* b)
            const noexcept
        {
            return Solution::nodesEq<false>(a, b);
        }
    };

    std::deque<Node> nodes;
    std::unordered_set<Node*, LookupHasher, LookupComparator> lookup;
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> tmp_path;
};
