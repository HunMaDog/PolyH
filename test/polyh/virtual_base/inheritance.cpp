#include "detail/polyh/virtual_base.hpp"

// Marklar headers
// External library headers
#include "../catch.hpp"
// C++ standard library headers

constexpr int forty_and_two{42};

template<typename Derived>
class Base : public marklar::detail::polyh::VirtualBase<Derived, Base> {
public:
    constexpr decltype(auto) interface() const noexcept
    {
        return this->underlying().underlying_function();
    }
};

class Derived : public Base<Derived> {
    friend Base<Derived>;

protected:
    constexpr int underlying_function() const noexcept
    {
        return forty_and_two;
    }
};

TEST_CASE("marklar::detail::polyh::VirtualBase should be provide derived class object when fully implemented the underlying functions")
{
    Derived const derived{};

    REQUIRE(forty_and_two == derived.interface());
}
