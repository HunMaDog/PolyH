#include "detail/polyh/virtual_base.hpp"

// Marklar headers
// External library headers
#include "../catch.hpp"
// C++ standard library headers

constexpr int zero{0};
constexpr int two{2};
constexpr int four{4};

/* VirtualBase is the super class in the diamond problem */

template<typename Derived>
class DiamondLeft : public marklar::detail::polyh::VirtualBase<Derived, DiamondLeft> {
public:
    /* Using public interface for avoid CRTP_VARIADIC_FRIEND macro */
    void increment(int number) noexcept
    {
        this->underlying().set(this->underlying().get() + number);
    }
};

template<typename Derived>
class DiamondRight : public marklar::detail::polyh::VirtualBase<Derived, DiamondRight> {
public:
    /* Using public interface for avoid CRTP_VARIADIC_FRIEND macro */
    void decrement(int number) noexcept
    {
        this->underlying().set(this->underlying().get() - number);
    }
};

class DiamondTop
    : public DiamondLeft<DiamondTop>
    , public DiamondRight<DiamondTop> {
public:
    DiamondTop()
        : DiamondLeft<DiamondTop>{}
        , DiamondRight<DiamondTop>{}
    {
    }

    void set(int number) noexcept
    {
        number_ = number;
    }

    int get() const noexcept
    {
        return number_;
    }

protected:
    int number_{zero};
};

TEST_CASE("marklar::detail::polyh::VirtualBase should be avoid diamond problem")
{
    DiamondTop diamond;

    /* Diamond left side call */
    diamond.set(four);
    CHECK(four == diamond.get());
    diamond.increment(two);
    REQUIRE((four + two) == diamond.get());

    /* Diamond right side call */
    diamond.set(four);
    CHECK(four == diamond.get());
    diamond.decrement(two);
    REQUIRE((four - two) == diamond.get());
}
