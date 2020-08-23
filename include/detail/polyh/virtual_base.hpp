/*
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 */
#ifndef MARKLAR_DETAIL_VIRTUAL_BASE_HPP
#define MARKLAR_DETAIL_VIRTUAL_BASE_HPP

// Marklar headers
// External library headers
// C++ standard library headers
#include <type_traits>

/*
 * Helper struct to achive multilevel inheritance
 */
namespace marklar::detail::polyh::tag
{
struct NoDerivedClass
{
};
} // namespace marklar::detail::polyh::tag

/*
 * Curiously recurring template pattern solution with multilevel and multiple inheritance
 */
namespace marklar::detail::polyh
{
/*
 * Derived   - We would like to obtain access to this type of instance
 * UniqueTag - Helper type to avoid the diamond problem without virtual inheritance
 */
template<typename Derived, template<typename...> class UniqueTag>
class VirtualBase {
protected:
    [[nodiscard]] constexpr Derived & underlying() noexcept
    {
        return static_cast<Derived &>(*this);
    }

    [[nodiscard]] constexpr Derived const & underlying() const noexcept
    {
        return static_cast<Derived const &>(*this);
    }
};

/*
 * Derived    - Current class
 * DirectBase - Base class of the current class
 * Substitute - Optional - New class which derived from the current class
 */
template<template<typename...> class Derived, template<typename...> class DirectBase, typename Substitute = tag::NoDerivedClass>
using ConstructDirectBase =
    DirectBase<std::conditional_t<std::is_same_v<Substitute, tag::NoDerivedClass>, Derived<tag::NoDerivedClass>, Substitute>>;

} // namespace marklar::detail::polyh

#endif // MARKLAR_DETAIL_VIRTUAL_BASE_HPP
