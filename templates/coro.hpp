#pragma once

#include <coroutine>
#include <print>
#include <source_location>

void print_location(
    const std::source_location location = std::source_location::current())
{
    std::println(
        "{}:{} -> {}",
        location.file_name(),
        location.line(),
        location.function_name());
}

template <
    typename YieldType,
    typename ReturnType = void,
    typename Enable = void>
struct Generator;

template <
    template <typename, typename> typename FinalPromiseT,
    typename YieldType,
    typename ReturnType>
struct GeneratorPromiseBase
{
    using FinalPromise = FinalPromiseT<YieldType, ReturnType>;
    using Generator = Generator<YieldType, ReturnType>;

    [[nodiscard]] constexpr std::suspend_never initial_suspend() noexcept
    {
        print_location();
        return {};
    }

    [[nodiscard]] constexpr std::suspend_always final_suspend() noexcept
    {
        print_location();
        return {};
    }

    Generator get_return_object()
    {
        print_location();
        return Generator(
            std::coroutine_handle<FinalPromise>::from_promise(
                *static_cast<FinalPromise*>(this)));
    }

    void unhandled_exception() noexcept
    {
        print_location();
        std::abort();
    }

    template <typename... Args>
    auto yield_value(Args&&... args)
    {
        print_location();
        yield_val = YieldType{std::forward<Args>(args)...};
        return std::suspend_always{};
    }

    YieldType yield_val{};
};

template <typename YieldType, typename ReturnType>
struct GeneratorPromiseR
    : public GeneratorPromiseBase<GeneratorPromiseR, YieldType, ReturnType>
{
    using Generator = Generator<YieldType, ReturnType>;

    template <typename... Args>
    void return_value(Args&&... args)
    {
        print_location();
        ret_val = ReturnType{std::forward<Args>(args)...};
    }

    ReturnType ret_val{};
};

template <typename YieldType, typename ReturnType>
struct GeneratorPromiseV
    : public GeneratorPromiseBase<GeneratorPromiseV, YieldType, ReturnType>
{
    void return_void() { print_location(); }
};

template <
    template <typename, typename> typename FinalGenerator,
    typename YieldType,
    typename ReturnType = void>
struct GeneratorBase
{
    using promise_type = std::conditional_t<
        std::same_as<ReturnType, void>,
        GeneratorPromiseV<YieldType, ReturnType>,
        GeneratorPromiseR<YieldType, ReturnType>>;
    using Handle = std::coroutine_handle<promise_type>;

    explicit GeneratorBase(Handle h) : handle(h) { print_location(); }
    GeneratorBase(const GeneratorBase&) = delete;
    GeneratorBase(GeneratorBase&&) = default;
    ~GeneratorBase()
    {
        print_location();
        if (handle) handle.destroy();
    }

    void resume() { handle.resume(); }

    Handle handle;
};

template <typename YieldType, typename ReturnType>
struct Generator<
    YieldType,
    ReturnType,
    std::enable_if_t<!std::same_as<ReturnType, void>>>
    : public GeneratorBase<Generator, YieldType, ReturnType>
{
    using Super = GeneratorBase<Generator, YieldType, ReturnType>;
    using Super::Super;

    const ReturnType& get_return_value() const
    {
        return this->handle.promise().ret_val;
    }

    ReturnType& get_return_value() & { return this->handle.promise().ret_val; }

    ReturnType get_return_value() &&
    {
        return std::move(this->handle.promise().ret_val);
    }
};

template <typename YieldType, typename ReturnType>
struct Generator<
    YieldType,
    ReturnType,
    std::enable_if_t<std::same_as<ReturnType, void>>>
    : public GeneratorBase<Generator, YieldType, ReturnType>
{
    using Super = GeneratorBase<Generator, YieldType, ReturnType>;
    using Super::Super;
};

// Generator<int, int> f()
// {
//     print_location();
//     co_yield 1;
//     co_return 42;
// }

// Generator<int> f()
// {
//     print_location();
//     co_yield 1;
//     co_return;
// }

// TEST(t2264_largest_3_same_digit_number_in_string, test_1)
// {
//     print_location();
//     auto task = f();
//     print_location();
//     task.resume();
//     print_location();
//     // std::println("Return value: {}", task.get_return_value());
// }
