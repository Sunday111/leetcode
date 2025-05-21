#pragma once

#include <cassert>
#include <concepts>
#include <format>
#include <string_view>
#include <vector>

template <typename T>
concept UnidirectedGraphNodeConcept = requires(T a, int x) {
    requires(
        std::same_as<std::decay_t<decltype(a.neighbors)>, std::vector<T*>>);

    // Has integral val property
    requires std::integral<std::remove_cvref_t<decltype(a.val)>>;

    // constructible from integral
    T{x};
};

template <UnidirectedGraphNodeConcept TNode>
class LeetCodeUnidirectedGraph
{
public:
    std::vector<TNode> nodes;

    [[nodiscard]] static constexpr std::vector<std::vector<uint32_t>>
    ParseAdjacencyList(std::string_view s)
    {
        std::vector<std::vector<uint32_t>> al;

        size_t i = 0;

        auto peek = [&]
        {
            return s[i];
        };

        auto take = [&]
        {
            return s[i++];
        };

        auto read_number = [&]() -> uint32_t
        {
            uint32_t r = 0;
            while (std::isdigit(peek()))
            {
                r *= 10;
                r += static_cast<uint8_t>(take() - '0');
            }

            return r;
        };

        assert(peek() == '[');
        take();

        while (peek() != ']')
        {
            auto& neighbours = al.emplace_back();
            assert(peek() == '[');
            take();

            while (peek() != ']')
            {
                neighbours.push_back(read_number());
                if (peek() == ',') take();
            }

            take();
            if (peek() == ',') take();
        }

        return al;
    }

    [[nodiscard]] static constexpr LeetCodeUnidirectedGraph FromAdjacencyList(
        const std::vector<std::vector<uint32_t>>& al,
        int value)
    {
        LeetCodeUnidirectedGraph r{};
        r.InitFromAdjacencyList(al, value);
        return r;
    }

    [[nodiscard]] static constexpr LeetCodeUnidirectedGraph
    FromAdjacencyListStr(std::string_view adjacency_list_str, int value)
    {
        LeetCodeUnidirectedGraph r{};
        auto adjacency_list = ParseAdjacencyList(adjacency_list_str);
        r.InitFromAdjacencyList(adjacency_list, value);
        return r;
    }

    [[nodiscard]] constexpr std::vector<std::vector<uint32_t>>
    MakeAdjacencyList() const
    {
        std::vector<std::vector<uint32_t>> al(nodes.size());

        for (size_t node_index = 0; node_index != nodes.size(); ++node_index)
        {
            auto& node = nodes[node_index];
            auto& neighbours_numbers = al[node_index];
            neighbours_numbers.reserve(node.neighbors.size());

            for (const auto* neighbour : node.neighbors)
            {
                neighbours_numbers.push_back(
                    static_cast<uint32_t>(
                        std::distance(nodes.data(), neighbour) + 1));
            }
        }

        return al;
    }

    [[nodiscard]] constexpr TNode* GetRoot()
    {
        if (nodes.empty()) return nullptr;
        return &nodes[0];
    }

    [[nodiscard]] static constexpr std::string AdjacencyListToStr(
        const std::vector<std::vector<uint32_t>>& al)
    {
        auto s = std::format("{}", al);
        s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
        return s;
    }

    [[nodiscard]] constexpr std::string MakeAdjacencyListStr() const
    {
        auto al = MakeAdjacencyList();
        return AdjacencyListToStr(al);
    }

    constexpr void InitFromAdjacencyList(
        const std::vector<std::vector<uint32_t>>& al,
        int value)
    {
        nodes.clear();
        nodes.resize(al.size(), TNode(value));
        for (size_t i = 0; i != al.size(); ++i)
        {
            auto& node = nodes[i];
            const auto& neighbours_numbers = al[i];
            node.neighbors.reserve(neighbours_numbers.size());
            for (uint32_t neighbour_number : neighbours_numbers)
            {
                assert(neighbour_number != 0);
                node.neighbors.push_back(&nodes[neighbour_number - 1]);
            }
        }
    }
};
