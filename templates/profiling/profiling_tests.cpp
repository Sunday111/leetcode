#include <print>
#include <thread>

#include "gtest/gtest.h"
#include "profiling.hpp"
#include "speedscope_json.hpp"

constexpr inline auto curr_frame = []() -> const profiling::Frame&
{
    auto& p = profiling::Profiler::Instance();
    return p.GetFrames()[p.current_frame_id.GetValue()];
};

constexpr inline auto curr_src = []() -> const profiling::SourceInfo&
{
    auto& p = profiling::Profiler::Instance();
    return p.GetSources()[curr_frame().source.GetValue()];
};

constexpr inline auto get_current_source_name = []() -> std::string_view
{
    return curr_src().name;
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
        ASSERT_EQ(curr_frame().child, kInvalidId);
        ASSERT_EQ(curr_frame().sibling, kInvalidId);
        ASSERT_EQ(curr_frame().status, Status::Started);

        {
            profiling::Scope _{"a"};
            ASSERT_EQ(curr_src().location.line(), __LINE__ - 1);
            ASSERT_EQ(curr_src().name, "a");
            ASSERT_EQ(curr_frame().child, kInvalidId);
            ASSERT_EQ(curr_frame().sibling, kInvalidId);
            ASSERT_EQ(curr_frame().status, Status::Started);

            profiling::FrameId child = kInvalidId;
            {
                profiling::Scope _{"b"};
                ASSERT_EQ(get_current_source_name(), "b");
                ASSERT_EQ(curr_frame().child, kInvalidId);
                ASSERT_EQ(curr_frame().sibling, kInvalidId);
                ASSERT_EQ(curr_frame().status, Status::Started);
                child = p.current_frame_id;
            }
            ASSERT_EQ(get_current_source_name(), "a");
            ASSERT_EQ(curr_frame().child, child);
            ASSERT_EQ(curr_frame().sibling, kInvalidId);
            ASSERT_EQ(curr_frame().status, Status::GotChild);

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

TEST(ProfilingTest, RepeatedRecordings)
{
    auto& p = profiling::Profiler::Instance();
    profiling::SourceId source = kInvalidId;
    for (int recording = 0; recording < 2; ++recording)
    {
        p.Start();
        EXPECT_EQ(p.GetFrames().size(), 1);
        {
            profiling::Scope scope{"repeated"};
            auto current_source = curr_frame().source;
            if (recording == 0) source = current_source;
            EXPECT_EQ(current_source, source);
            EXPECT_EQ(curr_src().name, "repeated");
        }
        p.Finish();
        EXPECT_FALSE(p.current_frame_id.IsValid());
        EXPECT_FALSE(p.last_child_frame_id.IsValid());
        ASSERT_EQ(p.GetFrames().size(), 2);
        const auto& root = p.GetFrames()[p.root_frame_id.GetValue()];
        EXPECT_EQ(root.status, profiling::Status::Completed);
        EXPECT_EQ(
            p.GetFrames()[root.child.GetValue()].status,
            profiling::Status::LastChild);
        EXPECT_FALSE(std::format("{}", profiling::SpeedScopeJSON{p}).empty());
    }

    p.Start();
    p.Finish();
    ASSERT_EQ(p.GetFrames().size(), 1);
    EXPECT_FALSE(p.GetFrames().front().child.IsValid());
    EXPECT_FALSE(p.current_frame_id.IsValid());
    EXPECT_FALSE(p.last_child_frame_id.IsValid());
}
