#include "detail/polyh/virtual_base.hpp"

// Marklar headers
// External library headers
#include "../catch.hpp"
// C++ standard library headers

constexpr int zero{0};
constexpr int one{1};
constexpr int two{2};
constexpr int four{4};
constexpr int forty_and_two{42};

template<typename Derived>
class Base : public marklar::detail::polyh::VirtualBase<Derived, Base> {
public:
    constexpr decltype(auto) interface_one() const noexcept
    {
        return this->underlying().underlying_one();
    }

    constexpr decltype(auto) interface_two() const noexcept
    {
        return this->underlying().underlying_two();
    }
};

template<typename Derived = marklar::detail::polyh::tag::NoDerivedClass>
class FirstDerived : public marklar::detail::polyh::ConstructDirectBase<FirstDerived, Base, Derived> {
    friend Base<FirstDerived<Derived>>;

protected:
    constexpr int underlying_one() const noexcept
    {
        return zero;
    }

    constexpr int underlying_two() const noexcept
    {
        return one;
    }
};

template<typename Derived = marklar::detail::polyh::tag::NoDerivedClass>
class SecondDerived : public marklar::detail::polyh::ConstructDirectBase<SecondDerived, FirstDerived, Derived> {
    friend Base<SecondDerived<Derived>>;

protected:
    constexpr int underlying_one() const noexcept
    {
        return forty_and_two;
    }
};

template<typename Derived = marklar::detail::polyh::tag::NoDerivedClass>
class ThirdDerived : public marklar::detail::polyh::ConstructDirectBase<ThirdDerived, SecondDerived, Derived> {
    friend Base<ThirdDerived<Derived>>;

protected:
    constexpr int underlying_one() const noexcept
    {
        return four;
    }

    constexpr int underlying_two() const noexcept
    {
        return two;
    }
};

TEST_CASE("marklar::detail::Crtp should be provide derived base class object when fully implemented the underlying functions")
{
    FirstDerived first{};
    REQUIRE(zero == first.interface_one()); // Should come from FirstDerived
    REQUIRE(one == first.interface_two());  // Should come from FirstDerived
}

TEST_CASE("marklar::detail::Crtp should be provide latest valid derived class object when partial implemented the underlying functions")
{
    SecondDerived second{};
    REQUIRE(forty_and_two == second.interface_one()); // Should come from SecondDerived
    REQUIRE(one == second.interface_two());           // Should come from FirstDerived
}

TEST_CASE(
    "marklar::detail::Crtp should be provide latest valid derived class object when already fully implemented the underlying functions")
{
    ThirdDerived third{};
    REQUIRE(four == third.interface_one()); // Should come from ThirdDerived
    REQUIRE(two == third.interface_two());  // Should come from ThirdDerived
}
