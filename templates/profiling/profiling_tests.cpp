#include <thread>

#include "gtest/gtest.h"
#include "profiling.hpp"

TEST(ProfilingTest, SourceId)
{
    auto src_id = profiling::register_source("test");
    auto& p = profiling::Profiler::Instance();
    auto& source_info = p.GetSourceInfo(src_id);
    ASSERT_TRUE(
        std::string_view{source_info.location.function_name()}.contains(
            "SourceId"));
    ASSERT_EQ(source_info.name, "test");
    std::println("function name: {}", source_info.location.function_name());
    std::println("file name: {}", source_info.location.file_name());
    std::println("line: {}", source_info.location.line());
    std::println("column: {}", source_info.location.column());
}

constexpr inline auto curr_entry = []() -> const profiling::ProfilerEntry&
{
    auto& p = profiling::Profiler::Instance();
    return p.entries[p.current_entry_id.GetValue()];
};

constexpr inline auto curr_src = []() -> const profiling::SourceInfo&
{
    auto& p = profiling::Profiler::Instance();
    return p.sources[curr_entry().source.GetValue()];
};

constexpr inline auto get_current_source_name = []() -> std::string_view
{
    return curr_src().name;
};

constexpr inline auto print_current_entry = []()
{
    std::println("{}", get_current_source_name());
};

TEST(ProfilingTest, ScopeExample)
{
    using profiling::Status;
    using namespace std::chrono_literals;
    auto& p = profiling::Profiler::Instance();
    p.Start();

    {
        profiling::Scope scope{"Experiment"};

        {
            profiling::Scope _{"a"};
            std::this_thread::sleep_for(100us);

            {
                profiling::Scope _{"b"};
                std::this_thread::sleep_for(150us);
            }

            {
                profiling::Scope _{"c"};
                std::this_thread::sleep_for(50us);

                {
                    profiling::Scope _{"d"};
                    std::this_thread::sleep_for(172us);
                }

                std::this_thread::sleep_for(250us);
            }

            {
                profiling::Scope _{"e"};
                std::this_thread::sleep_for(60us);
            }

            std::this_thread::sleep_for(315us);
        }

        std::this_thread::sleep_for(222us);
    }

    p.Finish();

    std::println("{}", profiling::SpeedScopeJSON{p});
}

TEST(ProfilingTest, Scope)
{
    using profiling::Status;
    auto& p = profiling::Profiler::Instance();
    p.Start();
    ASSERT_EQ(get_current_source_name(), p.kRootNodeName);

    {
        profiling::Scope scope{"Experiment"};
        ASSERT_EQ(curr_src().location.line(), __LINE__ - 1);
        ASSERT_EQ(curr_src().name, "Experiment");
        ASSERT_EQ(curr_entry().child, kInvalidId);
        ASSERT_EQ(curr_entry().sibling, kInvalidId);
        ASSERT_EQ(curr_entry().status, Status::Started);

        {
            profiling::Scope _{"a"};
            ASSERT_EQ(curr_src().location.line(), __LINE__ - 1);
            ASSERT_EQ(curr_src().name, "a");
            ASSERT_EQ(curr_entry().child, kInvalidId);
            ASSERT_EQ(curr_entry().sibling, kInvalidId);
            ASSERT_EQ(curr_entry().status, Status::Started);

            profiling::EntryId child = kInvalidId;
            {
                profiling::Scope _{"b"};
                ASSERT_EQ(get_current_source_name(), "b");
                ASSERT_EQ(curr_entry().child, kInvalidId);
                ASSERT_EQ(curr_entry().sibling, kInvalidId);
                ASSERT_EQ(curr_entry().status, Status::Started);
                child = p.current_entry_id;
            }
            ASSERT_EQ(get_current_source_name(), "a");
            ASSERT_EQ(curr_entry().child, child);
            ASSERT_EQ(curr_entry().sibling, kInvalidId);
            ASSERT_EQ(curr_entry().status, Status::GotChild);

            {
                profiling::Scope _{"c"};
                ASSERT_EQ(get_current_source_name(), "c");

                {
                    profiling::Scope _{"d"};
                    ASSERT_EQ(get_current_source_name(), "d");
                }
                ASSERT_EQ(get_current_source_name(), "c");
            }
            ASSERT_EQ(get_current_source_name(), "a");

            {
                profiling::Scope _{"e"};
                ASSERT_EQ(get_current_source_name(), "e");
            }
            ASSERT_EQ(get_current_source_name(), "a");
        }
        ASSERT_EQ(get_current_source_name(), "Experiment");
    }
    ASSERT_EQ(get_current_source_name(), "root");

    p.Finish();

    std::println("{}", profiling::SpeedScopeJSON{p});
}
