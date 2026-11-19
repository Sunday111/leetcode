#pragma once

#include <deque>
#include <map>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

class Solution
{
    struct Node
    {
        std::map<std::string_view, Node*> children{};
        bool marked = false;

        std::size_t hash(std::unordered_map<size_t, Node*>& unique)
        {
            if (children.size() == 0) return 0;

            std::size_t hash = 0;
            for (const auto& [child_name, node] : children)
            {
                hash_combine(hash, child_name);
                hash_combine(hash, node->hash(unique));
            }

            if (auto [iterator, inserted] = unique.try_emplace(hash, this);
                inserted)
            {
                iterator->second = this;
            }
            else
            {
                iterator->second->marked = marked = true;
            }
            return hash;
        }

        void pushOut(
            std::string_view name,
            std::vector<std::vector<std::string>>& dirs,
            std::vector<std::string>& cur)
        {
            if (marked) return;

            if (name.size()) dirs.push_back(cur);

            for (const auto& [child_name, child] : children)
            {
                cur.emplace_back(child_name);
                child->pushOut(child_name, dirs, cur);
                cur.pop_back();
            }
        }
    };

public:
    static std::vector<std::vector<std::string>> deleteDuplicateFolder(
        const std::vector<std::vector<std::string>>& paths)
    {
        Node root{};

        std::deque<Node> nodes;

        for (const auto& path : paths)
        {
            Node* cur = &root;
            for (const auto& dir : path)
            {
                if (auto it = cur->children.find(dir);
                    it == cur->children.end())
                {
                    auto& newNode = nodes.emplace_back();
                    cur->children.emplace(dir, &newNode);
                    cur = &newNode;
                }
                else
                {
                    cur = it->second;
                }
            }
        }

        std::unordered_map<std::size_t, Node*> unique;
        root.hash(unique);

        std::vector<std::vector<std::string>> out;
        std::vector<std::string> tmp;
        root.pushOut("", out, tmp);
        return out;
    }
};
