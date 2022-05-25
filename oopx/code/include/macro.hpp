#pragma once
#include <tuple>
#include <type_traits>
#include <cassert>
#include <iostream>
#define PRINT_MACRO(x) std::cout << x << std::endl;

template <class T, class... TArgs>
decltype(void(T{std::declval<TArgs>()...}), std::true_type{}) test_is_braces_constructible(int);
template <class, class...>
std::false_type test_is_braces_constructible(...);
template <class T, class... TArgs>
using is_braces_constructible = decltype(test_is_braces_constructible<T, TArgs...>(0));

struct any_type
{
    template <class T>
    constexpr operator T(); // non explicit
};

template <class T>
auto to_tuple(T &&object) noexcept
{
    using type = std::decay_t<T>;
    if constexpr (is_braces_constructible<type, any_type, any_type, any_type, any_type, any_type, any_type>{})
    {
        auto &&[p1, p2, p3, p4, p5, p6] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6);
    }
    if constexpr (is_braces_constructible<type, any_type, any_type, any_type, any_type, any_type>{})
    {
        auto &&[p1, p2, p3, p4, p5] = object;
        return std::make_tuple(p1, p2, p3, p4, p5);
    }
    if constexpr (is_braces_constructible<type, any_type, any_type, any_type, any_type>{})
    {
        auto &&[p1, p2, p3, p4] = object;
        return std::make_tuple(p1, p2, p3, p4);
    }
    else if constexpr (is_braces_constructible<type, any_type, any_type, any_type>{})
    {
        auto &&[p1, p2, p3] = object;
        return std::make_tuple(p1, p2, p3);
    }
    else if constexpr (is_braces_constructible<type, any_type, any_type>{})
    {
        auto &&[p1, p2] = object;
        return std::make_tuple(p1, p2);
    }
    else if constexpr (is_braces_constructible<type, any_type>{})
    {
        auto &&[p1] = object;
        return std::make_tuple(p1);
    }
    else
    {
        return std::make_tuple();
    }
}