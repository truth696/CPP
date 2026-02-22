#pragma once
#include <iostream>

template <typename T, typename U>
struct is_same : public std::false_type
{
};

template <typename T>
struct is_same<T, T> : public std::true_type
{
};

template<typename T,typename U>
inline constexpr bool is_same_v = is_same<T, U>::value;

template <typename T>
struct is_void : public std::false_type
{
};

template <>
struct is_void<void> : public std::true_type
{
};

template<typename T>
inline constexpr bool is_void_v = is_void<T>::value;

template <typename T>
struct is_pointer : public std::false_type
{
};

template <typename T>
struct is_pointer<T*> : public std::true_type
{
};

template <typename T>
struct is_pointer<T const*> : public std::true_type
{
};

template <typename T>
struct is_pointer<T volatile*> : public std::true_type
{
};

template <typename T>
struct is_pointer<T const volatile*> : public std::true_type
{
};

template <typename T>
inline constexpr bool is_pointer_v = is_pointer<T>::value;

template<typename T>
struct remove_reference
{
    using type = T;
};

template <typename T>
struct remove_reference<T&>
{
    using type = T;
};

template <typename T>
struct remove_reference<T&&>
{
    using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

template <typename T>
struct add_reference
{
    using type = T&;
};

template <typename T>
struct add_reference<T&>
{
    using type = T&&;
};

template <typename T>
struct add_reference<T&&>
{
    using type = T&&;
};

template <typename T>
using add_reference_t = typename add_reference<T>::type;


template <typename T>
struct is_reference : std::false_type
{
};

template <typename T>
struct is_reference<T&&> : std::true_type
{
};
template <typename T>
struct is_reference<T&> : std::true_type
{
};

template <typename T>
inline constexpr bool is_reference_v = is_reference<T>::value;


template <typename T>
struct is_const : std::false_type
{

};

template <typename T>
struct is_const<const T> : std::true_type
{

};

template <typename T>
inline constexpr bool is_const_v = is_const<T>::value;


template <typename T>
struct remove_const
{
    using type = T;
};

template <typename T>
struct remove_const<const T>
{
    using type = T;
};

template <typename T>
using remove_const_t = typename remove_const<T>::type;

template <typename From, typename To>
struct is_convertible {
    template <typename T, typename F>
    static auto test(int) -> decltype(static_cast<T>(std::declval<F>()), std::true_type{});
    
    template <typename T, typename F>
    static std::false_type test(...);
    
    constexpr static bool value = decltype(test<To, From>(0))::value;
};

template <typename T, typename U>
constexpr static bool is_convertible_v = is_convertible<T,U>::value;


template <typename Base, typename Derived>
struct is_base_of : std::false_type
{
    template <typename B>
    static auto test(const B*) -> decltype(std::true_type{});

    template <typename B, typename D>
    static std::false_type test(...);

    constexpr static bool value = decltype(test(std::declval<Derived*>()))::value;
};

template <typename Base, typename Derived>
constexpr bool is_base_of_v = is_base_of<Base, Derived>::value;



template <typename T>
struct is_default_constructable 
{
    template <typename N>
    static auto test(int) -> decltype(N(), std::true_type{});

    template  <typename N>
    static std::false_type test(...);

    constexpr static bool value = decltype(test<T>(0))::value; 
};

template <typename T>
constexpr static bool is_default_constructable_v = is_default_constructable<T>::value;


template <typename T>
struct has_operator_plus 
{
    template <typename N>
    static auto test(int) -> decltype(std::declval<N>() + std::declval<N>(), std::true_type{});

    template  <typename N>
    static std::false_type test(...);

    constexpr static bool value = decltype(test<T>(0))::value; 
};

template <typename T>
constexpr static bool has_operator_plus_v = has_operator_plus<T>::value;


template <typename T>
struct remove_volatile {
    using type = T;
};

template <typename T>
struct remove_volatile<volatile T> {
    using type = T;
};

template <typename T, std::size_t N>
struct remove_volatile<volatile T[N]> {
    using type = T[N];
};

template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

template <typename T>
struct decay
{
    using type = remove_const_t<remove_volatile_t<T>>;
};

template <typename T>
using decay_t = typename decay<T>::type;


template <size_t N>
struct factorial 
{
    constexpr static size_t value = N <= 1 ? 1 : N * factorial<N-1>::value;
};

template <>
struct factorial<0> {
    constexpr static std::size_t value = 1;
};


template <size_t N>
constexpr size_t factorial_v = factorial<N>::value;
