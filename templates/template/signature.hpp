#pragma once

#include <tuple>

template <typename T>
struct Signature;

// function
template <typename Ret_, typename... Args_>
struct Signature<Ret_ (*)(Args_...)>
{
    using Ret = Ret_;
    using Class = void;
    using Args = std::tuple<Args_...>;
    static constexpr bool Const = false;
    static constexpr bool Noexcept = false;
    static constexpr bool Volatile = false;
    static constexpr bool Pure = true;
    static constexpr bool LRef = false;
    static constexpr bool RRef = false;
};

// noexcept function
template <typename Ret_, typename... Args_>
struct Signature<Ret_ (*)(Args_...) noexcept> : Signature<Ret_ (*)(Args_...)>
{
    static constexpr bool Noexcept = true;
};

// method
template <typename Ret_, typename Class_, typename... Args_>
struct Signature<Ret_ (Class_::*)(Args_...)> : Signature<Ret_ (*)(Args_...)>
{
    using Class = Class_;
    static constexpr bool Pure = false;
};

#ifndef SIGNATURE_METHOD_SPECIALIZATION
#define SIGNATURE_METHOD_SPECIALIZATION(qualifiers)              \
    template <typename Ret_, typename Class_, typename... Args_> \
    struct Signature<Ret_ (Class_::*)(Args_...) qualifiers>      \
        : Signature<Ret_ (Class_::*)(Args_...)>
#else
static_assert(false, "Name collision with test macro");
#endif

SIGNATURE_METHOD_SPECIALIZATION(&)
{
    static constexpr bool LRef = true;
};
SIGNATURE_METHOD_SPECIALIZATION(&&)
{
    static constexpr bool RRef = true;
};
SIGNATURE_METHOD_SPECIALIZATION(const)
{
    static constexpr bool Const = true;
};
SIGNATURE_METHOD_SPECIALIZATION(const&)
{
    static constexpr bool Const = true;
    static constexpr bool LRef = true;
};
SIGNATURE_METHOD_SPECIALIZATION(const&&)
{
    static constexpr bool Const = true;
    static constexpr bool RRef = true;
};
SIGNATURE_METHOD_SPECIALIZATION(noexcept)
{
    static constexpr bool Noexcept = true;
};
SIGNATURE_METHOD_SPECIALIZATION(& noexcept)
{
    static constexpr bool Noexcept = true;
    static constexpr bool LRef = true;
};
SIGNATURE_METHOD_SPECIALIZATION(&& noexcept)
{
    static constexpr bool Noexcept = true;
    static constexpr bool RRef = true;
};
SIGNATURE_METHOD_SPECIALIZATION(volatile)
{
    static constexpr bool Volatile = true;
};
SIGNATURE_METHOD_SPECIALIZATION(volatile&)
{
    static constexpr bool Volatile = true;
    static constexpr bool LRef = true;
};
SIGNATURE_METHOD_SPECIALIZATION(volatile&&)
{
    static constexpr bool Volatile = true;
    static constexpr bool RRef = true;
};
SIGNATURE_METHOD_SPECIALIZATION(const noexcept)
{
    static constexpr bool Const = true;
    static constexpr bool Noexcept = true;
};
SIGNATURE_METHOD_SPECIALIZATION(const& noexcept)
{
    static constexpr bool Const = true;
    static constexpr bool Noexcept = true;
    static constexpr bool LRef = true;
};
SIGNATURE_METHOD_SPECIALIZATION(const&& noexcept)
{
    static constexpr bool Const = true;
    static constexpr bool Noexcept = true;
    static constexpr bool RRef = true;
};
SIGNATURE_METHOD_SPECIALIZATION(const volatile)
{
    static constexpr bool Const = true;
    static constexpr bool Volatile = true;
};
SIGNATURE_METHOD_SPECIALIZATION(const volatile&)
{
    static constexpr bool Const = true;
    static constexpr bool Volatile = true;
    static constexpr bool LRef = true;
};
SIGNATURE_METHOD_SPECIALIZATION(const volatile&&)
{
    static constexpr bool Const = true;
    static constexpr bool Volatile = true;
    static constexpr bool RRef = true;
};
SIGNATURE_METHOD_SPECIALIZATION(volatile noexcept)
{
    static constexpr bool Volatile = true;
    static constexpr bool Noexcept = true;
};
SIGNATURE_METHOD_SPECIALIZATION(volatile& noexcept)
{
    static constexpr bool Volatile = true;
    static constexpr bool Noexcept = true;
    static constexpr bool LRef = true;
};
SIGNATURE_METHOD_SPECIALIZATION(volatile&& noexcept)
{
    static constexpr bool Volatile = true;
    static constexpr bool Noexcept = true;
    static constexpr bool RRef = true;
};
SIGNATURE_METHOD_SPECIALIZATION(const volatile noexcept)
{
    static constexpr bool Const = true;
    static constexpr bool Volatile = true;
    static constexpr bool Noexcept = true;
};
SIGNATURE_METHOD_SPECIALIZATION(const volatile& noexcept)
{
    static constexpr bool Const = true;
    static constexpr bool Volatile = true;
    static constexpr bool Noexcept = true;
    static constexpr bool LRef = true;
};
SIGNATURE_METHOD_SPECIALIZATION(const volatile&& noexcept)
{
    static constexpr bool Const = true;
    static constexpr bool Volatile = true;
    static constexpr bool Noexcept = true;
    static constexpr bool RRef = true;
};

#undef SIGNATURE_METHOD_SPECIALIZATION

#ifndef SIGNATURE_TEST_METHOD
#define SIGNATURE_TEST_METHOD(pre_qualifiers, name, qualifiers) \
    pre_qualifiers int name(float, double) qualifiers           \
    {                                                           \
        return 42;                                              \
    }
#else
static_assert(false, "Name collision with test macro");
#endif
