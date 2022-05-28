#pragma once
/**
 * MACROS
 *
 * Contains macros for easier coding.
 *  PRINT_MACRO: print the value of a macro
 *  STR_EQ: check if two var are stringly equal
 *
 * It also have type casting macros.
 */
#include <tuple>
#include <type_traits>
#include <cassert>
#include <iostream>

#define PRINT_MACRO(x) std::cout << x << std::endl;
// 字符等价：由于double转string会出现精度丢失，所以只能用STR_EQ来对反序列化的都变了类型进行检查
#define STR_EQ(VALUE_1, VALUE_2) (std::to_string(VALUE_1)) == (std::to_string(VALUE_2))

// type casting macros
// cast a struct to a tuple
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
    // 你可以在这里添加更多变量的情况
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

// 用户定义的类型转换
// 下面是其具体实现的方式

#define serialize_user(VAR, FILE)        \
    {                                    \
        auto tup = struct_to_tuple(VAR); \
        serialize(tup, FILE);            \
    }
#define deserialize_user(VAR, FILE)       \
    {                                     \
        auto tup1 = struct_to_tuple(VAR); \
        deserialize(tup1, FILE);          \
        VAR = tuple_to_struct(tup1, VAR); \
    }
// 包含模式
#define serialize_user_m(VAR, FILE, MODE) \
    {                                     \
        auto tup = struct_to_tuple(VAR);  \
        MODE::serialize(tup, FILE);       \
    }
#define deserialize_user_m(VAR, FILE, MODE) \
    {                                       \
        auto tup1 = struct_to_tuple(VAR);   \
        MODE::deserialize(tup1, FILE);      \
        VAR = tuple_to_struct(tup1, VAR);   \
    }

// 包含名称
#define serialize_user_n(VAR, FILE, NAME)      \
    {                                          \
        auto tup = struct_to_tuple(VAR);       \
        XMLSerial::serialize(tup, FILE, NAME); \
    }
#define deserialize_user_n(VAR, FILE, NAME)       \
    {                                             \
        auto tup1 = struct_to_tuple(VAR);         \
        XMLSerial::deserialize(tup1, FILE, NAME); \
        VAR = tuple_to_struct(tup1, VAR);         \
    }
