#include "my_type_traits.hpp"
#include <iostream>
#include <string>

struct Base {};
struct Derived : Base {};
struct Unrelated {};

struct NoDefault { NoDefault(int) {} };

int main() {
    std::cout << std::boolalpha;

    // is_same
    static_assert(is_same_v<int,int>);
    static_assert(!is_same_v<int,float>);

    // is_void
    static_assert(is_void_v<void>);
    static_assert(!is_void_v<int>);

    // is_pointer
    static_assert(is_pointer_v<int*>);
    static_assert(is_pointer_v<const int*>);
    static_assert(!is_pointer_v<int>);

    // references
    static_assert(is_reference_v<int&>);
    static_assert(is_reference_v<int&&>);
    static_assert(!is_reference_v<int>);

    // const
    static_assert(is_const_v<const int>);
    static_assert(!is_const_v<int>);

    // remove_const / remove_volatile / decay
    static_assert(is_same_v<remove_const_t<const int>, int>);
    static_assert(is_same_v<remove_volatile_t<volatile int>, int>);
    static_assert(is_same_v<decay_t<const volatile int>, int>);

    // factorial
    static_assert(factorial_v<0> == 1);
    static_assert(factorial_v<1> == 1);
    static_assert(factorial_v<5> == 120);

    // is_convertible
    static_assert(is_convertible_v<int,float>);
    static_assert(!is_convertible_v<std::string,int>);

    // is_base_of
    static_assert(is_base_of_v<Base, Derived>);
    static_assert(is_base_of_v<Derived, Base>);
    static_assert(is_base_of_v<Base, Unrelated>);

    // is_default_constructable
    static_assert(is_default_constructable_v<int>);
    static_assert(!is_default_constructable_v<NoDefault>);

    // has_operator_plus
    static_assert(has_operator_plus_v<int>);
    static_assert(!has_operator_plus_v<NoDefault>);

    std::cout << "All static_asserts passed!\n";
}