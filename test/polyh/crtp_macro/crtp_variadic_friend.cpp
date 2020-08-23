#include "detail/polyh/crtp_macro.hpp"
#include "detail/polyh/virtual_base.hpp"

// Marklar headers
// External library headers
#include "../catch.hpp"
// C++ standard library headers

constexpr int zero{0};
constexpr int forty_and_two{42};

template<template<typename> class... Functionality>
class FinalDerived
    : public Functionality<FinalDerived<Functionality...>>...
{
    CRTP_VARIADIC_FRIEND(Functionality, Functionality<FinalDerived<Functionality...>>)

public:
    FinalDerived(int number)
        : Functionality<FinalDerived<Functionality...>>()...
        , protected_variable_ {number}
    {}

    constexpr int get() const
    {
        return protected_variable_;
    }

protected:
    int protected_variable_;
};

template<typename Derived>
struct Increment
    : marklar::detail::polyh::VirtualBase<Derived, Increment>
{
    void increment(int an_value)
    {
        this->underlying().protected_variable_ += an_value;
    }
};

template<typename Derived>
struct Decrement
    : marklar::detail::polyh::VirtualBase<Derived, Decrement>
{
    void decrement(int an_value)
    {
        this->underlying().protected_variable_ -= an_value;
    }
};

template<typename Derived>
struct Multiplication
    : marklar::detail::polyh::VirtualBase<Derived, Multiplication>
{
    void multiplication(int an_value)
    {
        this->underlying().protected_variable_ *= an_value;
    }
};

TEST_CASE("CRTP_VARIADIC_FRIEND should be work without template paramater")
{
    FinalDerived<> an_object{forty_and_two};
    REQUIRE(forty_and_two == an_object.get());
}

TEST_CASE("CRTP_VARIADIC_FRIEND should be work with one template paramater")
{
    FinalDerived<Increment> an_object{zero};

    an_object.increment(forty_and_two);

    REQUIRE(forty_and_two == an_object.get());
}

TEST_CASE("CRTP_VARIADIC_FRIEND should be work with N template paramaters")
{
    FinalDerived<Increment, Decrement, Multiplication> an_object{forty_and_two};

    an_object.decrement(forty_and_two);
    REQUIRE(zero == an_object.get());

    an_object.increment(forty_and_two);
    REQUIRE(forty_and_two == an_object.get());

    an_object.multiplication(zero);
    REQUIRE(zero == an_object.get());
}
