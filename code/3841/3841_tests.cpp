#include <algorithm>
#include <array>
#include <cstddef>
#include <functional>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include "3841_test_cases.hpp"
#include "gtest/gtest.h"

class t3841 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3841, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3841,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });

TEST(t3841Regression, UpdatesRootAndEndpoints)
{
    const std::vector<std::vector<int>> edges{{0, 1}, {0, 2}};
    const std::string labels = "abc";
    const std::vector<std::string> queries{
        "query 1 2",
        "update 0 b",
        "query 1 2",
        "query 0 2",
        "update 2 b",
        "query 1 2",
        "update 1 z",
        "query 1 2",
        "query 1 0",
        "query 1 1",
        "update 1 z",
        "query 1 2"};
    Solution solution;
    EXPECT_EQ(
        solution.palindromePath(3, edges, labels, queries),
        (std::vector<bool>{false, true, false, true, true, false, true, true}));
    EXPECT_EQ(labels, "abc");
}

TEST(t3841Regression, SingleVertexAndNoQueries)
{
    Solution solution;
    std::vector<std::string> queries{
        "query 0 0",
        "update 0 z",
        "query 0 0",
        "update 0 a",
        "query 0 0"};
    EXPECT_EQ(
        solution.palindromePath(1, {}, "a", queries),
        (std::vector<bool>{true, true, true}));
    queries = {"update 0 z", "update 0 z"};
    EXPECT_TRUE(solution.palindromePath(1, {}, "a", queries).empty());
}

TEST(t3841Regression, MaximumQueryCount)
{
    const Solution solution;
    std::vector<std::string> queries(50'000, "query 0 0");
    EXPECT_EQ(
        solution.palindromePath(1, {}, "a", queries),
        std::vector<bool>(queries.size(), true));
}

TEST(t3841Regression, LeadingAndTrailingUpdatesPreserveInputs)
{
    const std::vector<std::vector<int>> edges{{0, 1}, {1, 2}};
    const std::string labels = "abc";
    std::vector<std::string> queries{
        "update 0 b",
        "update 0 c",
        "update 2 b",
        "query 0 2",
        "update 1 a",
        "query 0 2",
        "update 0 a",
        "update 1 z"};
    const auto original_queries = queries;
    Solution solution;
    EXPECT_EQ(
        solution.palindromePath(3, edges, labels, queries),
        (std::vector<bool>{true, false}));
    EXPECT_EQ(queries, original_queries);
    EXPECT_EQ(labels, "abc");

    queries = {"update 0 b", "update 1 c", "update 2 a"};
    const auto updates = queries;
    EXPECT_TRUE(solution.palindromePath(3, edges, labels, queries).empty());
    EXPECT_EQ(queries, updates);
    EXPECT_EQ(labels, "abc");

    queries = {"query 0 2", "query 1 1"};
    EXPECT_EQ(
        solution.palindromePath(3, edges, labels, queries),
        (std::vector<bool>{false, true}));
}

TEST(t3841Regression, MatchesExplicitPathCounts)
{
    std::mt19937 generator(3841);
    Solution solution;
    for (u32 trial = 0; trial != 40; ++trial)
    {
        SCOPED_TRACE(trial);
        const u32 n = trial % 12 + 1;
        std::vector<u32> parent(n), depths(n);
        std::vector<u32> vertices(n);
        std::iota(vertices.begin(), vertices.end(), u32{0});
        std::shuffle(vertices.begin() + 1, vertices.end(), generator);
        std::vector<std::vector<int>> edges;
        for (u32 i = 1; i != n; ++i)
        {
            const u32 vertex = vertices.at(i);
            parent.at(vertex) = vertices.at(generator() % i);
            depths.at(vertex) = depths.at(parent.at(vertex)) + 1;
            edges.push_back(
                {static_cast<int>(vertex),
                 static_cast<int>(parent.at(vertex))});
        }
        std::ranges::shuffle(edges, generator);
        std::string labels(n, 'a');
        for (char& c : labels)
        {
            c = static_cast<char>('a' + generator() % 26);
        }
        auto current = labels;
        std::vector<std::string> queries;
        std::vector<bool> expected;
        for (u32 step = 0; step != 90; ++step)
        {
            const u32 u = static_cast<u32>(generator() % n);
            if (step % 3 == 0)
            {
                const char c = static_cast<char>('a' + generator() % 26);
                queries.push_back("update " + std::to_string(u) + ' ' + c);
                current.at(u) = c;
            }
            else
            {
                const u32 v = static_cast<u32>(generator() % n);
                queries.push_back(
                    "query " + std::to_string(u) + ' ' + std::to_string(v));
                std::array<u32, 26> counts{};
                const auto add = [&](u32 vertex)
                {
                    ++counts.at(
                        static_cast<std::size_t>(current.at(vertex) - 'a'));
                };
                u32 a = u, b = v;
                while (depths.at(a) > depths.at(b))
                {
                    add(a);
                    a = parent.at(a);
                }
                while (depths.at(b) > depths.at(a))
                {
                    add(b);
                    b = parent.at(b);
                }
                while (a != b)
                {
                    add(a);
                    add(b);
                    a = parent.at(a);
                    b = parent.at(b);
                }
                add(a);
                expected.push_back(
                    std::ranges::count_if(
                        counts,
                        [](u32 count) { return count % 2 != 0; }) <= 1);
            }
        }
        const auto original_queries = queries;
        EXPECT_EQ(solution.palindromePath(n, edges, labels, queries), expected);
        EXPECT_EQ(queries, original_queries);
    }
}

TEST(t3841Regression, MaximumDepth)
{
    constexpr u32 n = Solution::kMaxN;
    std::vector<std::vector<int>> edges;
    edges.reserve(n - 1);
    for (u32 i = 1; i != n; ++i)
    {
        edges.push_back({static_cast<int>(i - 1), static_cast<int>(i)});
    }
    const std::string labels(n, 'a');
    std::vector<std::string> queries{
        "query 0 49999",
        "update 49999 z",
        "query 0 49999",
        "query 49999 49999",
        "query 1 49999",
        "update 0 z",
        "query 0 49999",
        "query 0 0"};
    Solution solution;
    EXPECT_EQ(
        solution.palindromePath(n, edges, labels, queries),
        (std::vector<bool>{true, false, true, true, true, true}));
}

TEST(t3841Regression, MaximumWidth)
{
    constexpr u32 n = Solution::kMaxN;
    std::vector<std::vector<int>> edges;
    edges.reserve(n - 1);
    for (u32 i = 1; i != n; ++i)
    {
        edges.push_back({0, static_cast<int>(i)});
    }
    const std::string labels(n, 'a');
    std::vector<std::string> queries{
        "query 1 49999",
        "update 49999 z",
        "query 1 49999",
        "query 0 49999",
        "update 0 b",
        "query 1 49999",
        "update 1 z",
        "query 1 49999"};
    Solution solution;
    EXPECT_EQ(
        solution.palindromePath(n, edges, labels, queries),
        (std::vector<bool>{true, true, false, false, true}));
}

TEST(t3841Regression, DeepBranches)
{
    constexpr u32 n = Solution::kMaxN;
    std::vector<std::vector<int>> edges;
    edges.reserve(n - 1);
    for (u32 i = 1; i != n; ++i)
    {
        const u32 parent = i == n / 2 ? 0 : i - 1;
        edges.push_back({static_cast<int>(parent), static_cast<int>(i)});
    }
    const std::string labels(n, 'a');
    std::vector<std::string> queries{
        "query 24999 49999",
        "update 0 z",
        "query 24999 49999",
        "update 24999 z",
        "query 24999 49999",
        "query 1 24999",
        "query 25000 49999",
        "update 25000 b",
        "query 24999 49999",
        "query 49999 49999"};
    Solution solution;
    EXPECT_EQ(
        solution.palindromePath(n, edges, labels, queries),
        (std::vector<bool>{true, false, true, true, true, false, true}));
}
