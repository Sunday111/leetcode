#pragma once

#include <limits>

struct InvalidId
{
};

inline constexpr InvalidId kInvalidId{};

template <
    typename Tag,
    typename Repr_,
    Repr_ invalid_id = std::numeric_limits<Repr_>::max()>
class TaggedID
{
public:
    using Repr = Repr_;

private:
    explicit constexpr TaggedID(const Repr& value) noexcept : value_(value) {}

public:
    // NOLINTNEXTLINE
    constexpr TaggedID(InvalidId) noexcept : value_{invalid_id} {}

    constexpr TaggedID(const TaggedID&) noexcept = default;
    constexpr TaggedID(TaggedID&&) noexcept = default;
    constexpr TaggedID& operator=(const TaggedID&) noexcept = default;
    constexpr TaggedID& operator=(TaggedID&&) noexcept = default;

    static constexpr TaggedID FromValue(const Repr& repr)
    {
        return TaggedID(repr);
    }

    [[nodiscard]] constexpr const Repr& GetValue() const noexcept
    {
        return value_;
    }

    [[nodiscard]] constexpr bool IsValid() const noexcept
    {
        return value_ != invalid_id;
    }

    [[nodiscard]] constexpr bool operator<=>(const TaggedID&) const noexcept =
        default;

private:
    Repr value_ = invalid_id;
};
