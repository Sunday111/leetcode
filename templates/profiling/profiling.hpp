#pragma once

#include <cassert>
#include <chrono>
#include <deque>
#include <source_location>

#include "integral_aliases.hpp"
#include "tagged_id.hpp"

namespace profiling
{

namespace tags
{
struct FrameID;
struct SourceID;

}  // namespace tags

using Clock = std::chrono::high_resolution_clock;
using TimePoint = Clock::time_point;

using FrameId = TaggedID<tags::FrameID, u64>;
using SourceId = TaggedID<tags::SourceID, u32>;

enum class Status : u8
{
    // Function is in progress, source and start time are available
    Started,

    // Stepped in. Child is available
    GotChild,

    // Function has completed execution.
    // This state can transition to GotSibling or LastChild
    Completed,

    GotSibling,
    LastChild,
};

struct Frame
{
    SourceId source = kInvalidId;

    TimePoint start;
    TimePoint finish;

    FrameId child = kInvalidId;
    FrameId sibling = kInvalidId;

    Status status = Status::Started;
};

struct SourceInfo
{
    std::string_view name;
    std::source_location location;
};

class Profiler
{
public:
    static Profiler& Instance()
    {
        static Profiler instance;
        return instance;
    }

    inline static constexpr std::string_view kRootNodeName = "root";

    FrameId root_frame_id = kInvalidId;
    FrameId current_frame_id = kInvalidId;
    FrameId last_child_frame_id = kInvalidId;

    [[nodiscard]] inline FrameId BeginFrame(SourceId src_id)
    {
        FrameId current_id = CreateFrame(src_id);

        auto& current = frames[current_id.GetValue()];
        current.start = Clock::now();

        if (last_child_frame_id.IsValid())
        {
            auto& sibling = frames[last_child_frame_id.GetValue()];
            sibling.sibling = current_id;
            sibling.status = Status::GotSibling;
            last_child_frame_id = kInvalidId;
        }
        else
        {
            auto& parent = frames[current_frame_id.GetValue()];
            parent.child = current_id;
            parent.status = Status::GotChild;
        }

        current_frame_id = current_id;
        return current_id;
    }

    void EndFrame([[maybe_unused]] FrameId current_id, FrameId parent_id)
    {
        auto& current = frames[current_id.GetValue()];
        current.finish = Clock::now();
        current.status = Status::Completed;

        assert(current_id == current_frame_id);
        if (last_child_frame_id != kInvalidId)
        {
            auto& last_child = frames[last_child_frame_id.GetValue()];
            last_child.status = Status::LastChild;
        }

        last_child_frame_id = current_frame_id;
        current_frame_id = parent_id;
    }

    void Start(std::source_location location = std::source_location::current())
    {
        assert(
            !root_frame_id.IsValid() && !current_frame_id.IsValid() &&
            !last_child_frame_id.IsValid());
        root_frame_id = CreateFrame(RegisterSource(
            SourceInfo{
                .name = kRootNodeName,
                .location = location,
            }));
        auto& frame = frames[root_frame_id.GetValue()];
        frame.start = Clock::now();
        current_frame_id = root_frame_id;
    }

    void Finish()
    {
        assert(current_frame_id == root_frame_id);
        auto& root_frame = frames[root_frame_id.GetValue()];
        root_frame.finish = Clock::now();
        root_frame.status = Status::Completed;
    }

    [[nodiscard]] inline SourceId RegisterSource(SourceInfo&& info)
    {
        SourceId id = SourceId::FromValue(static_cast<u32>(sources.size()));
        sources.emplace_back(std::move(info));  // NOLINT
        return id;
    }

    [[nodiscard]] inline constexpr auto& GetSources() const noexcept
    {
        return sources;
    }

    [[nodiscard]] inline constexpr auto& GetFrames() const noexcept
    {
        return frames;
    }

private:
    [[nodiscard]] FrameId CreateFrame(SourceId src)
    {
        FrameId frame_id =
            FrameId::FromValue(static_cast<FrameId::Repr>(frames.size()));
        frames.emplace_back().source = src;
        return frame_id;
    }

    Profiler() {}
    std::deque<SourceInfo> sources;
    std::deque<Frame> frames;
};

template <auto = []{}>
struct Scope
{
    FrameId current = kInvalidId;
    FrameId parent = kInvalidId;

    explicit Scope(
        std::string_view short_name,
        std::source_location location =
            std::source_location::current()) noexcept
    {
        auto& p = profiling::Profiler::Instance();
        static auto src_id = p.RegisterSource({
            .name = short_name,
            .location = location,
        });

        parent = p.current_frame_id;
        current = p.BeginFrame(src_id);
    }

    ~Scope() noexcept { Profiler::Instance().EndFrame(current, parent); }
};

}  // namespace profiling
