#pragma once
#include <tuple>
#include <type_traits>
#include <cassert>
#include <iostream>

#define PRINT_MACRO(x) std::cout << x << std::endl;
#define STR_EQ(VALUE_1, VALUE_2) (std::to_string(VALUE_1)) == (std::to_string(VALUE_2))

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
auto struct_to_tuple(T &&object) noexcept
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

template <class S, std::size_t... Is, class Tup>
S tuple_to_struct(std::index_sequence<Is...>, Tup &&tup, const S &something)
{
    using std::get;
    return {get<Is>(std::forward<Tup>(tup))...};
}
template <class S, class Tup>
S tuple_to_struct(Tup &&tup, const S &something)
{
    using T = std::remove_reference_t<Tup>;

    return tuple_to_struct(
        std::make_index_sequence<std::tuple_size<T>{}>{},
        std::forward<Tup>(tup), something);
}

#define serialize_user(VAR, FILE)        \
    {                                    \
        auto tup = struct_to_tuple(VAR); \
        serialize(tup, FILE);            \
    }
#define serialize_user_n(VAR, FILE, NAME) \
    {                                     \
        auto tup = struct_to_tuple(VAR);  \
        serialize(tup, FILE, NAME);       \
    }

#define serialize_user_m(VAR, FILE, MODE) \
    {                                     \
        auto tup = struct_to_tuple(VAR);  \
        MODE::serialize(tup, FILE);       \
    }

#define serialize_user_n_m(VAR, FILE, NAME, MODE) \
    {                                             \
        auto tup = struct_to_tuple(VAR);          \
        MODE::serialize(tup, FILE, NAME);         \
    }

#define deserialize_user(VAR, FILE)       \
    {                                     \
        auto tup1 = struct_to_tuple(VAR); \
        deserialize(tup1, FILE);          \
        VAR = tuple_to_struct(tup1, VAR); \
    }

#define deserialize_user_n(VAR, FILE, NAME) \
    {                                       \
        auto tup1 = struct_to_tuple(VAR);   \
        deserialize(tup1, FILE, NAME);      \
        VAR = tuple_to_struct(tup1, VAR);   \
    }

#define deserialize_user_m(VAR, FILE, MODE) \
    {                                       \
        auto tup1 = struct_to_tuple(VAR);   \
        MODE::deserialize(tup1, FILE);      \
        VAR = tuple_to_struct(tup1, VAR);   \
    }

#define deserialize_user_n_m(VAR, FILE, NAME, MODE) \
    {                                               \
        auto tup1 = struct_to_tuple(VAR);           \
        MODE::deserialize(tup1, FILE, NAME);        \
        VAR = tuple_to_struct(tup1, VAR);           \
    }
