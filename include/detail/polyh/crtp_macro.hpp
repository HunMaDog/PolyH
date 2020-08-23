/*
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 */
#ifndef MARKLAR_DETAIL_CRTP_MACRO_HPP
#define MARKLAR_DETAIL_CRTP_MACRO_HPP

// Marklar headers
// External library headers
// C++ standard library headers
#include <tuple>

/*
 * Helper macro for be more expressive
 */
#ifndef CRTP_UNDERLYING

#    define CRTP_UNDERLYING this->underlying()

#endif // CRTP_UNDERLYING

/*
 * Helper macro for make variadic virtual base classes to friends
 */
#ifndef CRTP_VARIADIC_FRIEND

// M - Macro
// N - Number
// P - Packed parameters
// T - Type
#    define CRTP_FRIEND_REPEATER_2(M, N, P, T) M(N, P, T) M(N + 1, P, T)
#    define CRTP_FRIEND_REPEATER_4(M, N, P, T) CRTP_FRIEND_REPEATER_2(M, N, P, T) CRTP_FRIEND_REPEATER_2(M, N + 2, P, T)
#    define CRTP_FRIEND_REPEATER_8(M, N, P, T) CRTP_FRIEND_REPEATER_4(M, N, P, T) CRTP_FRIEND_REPEATER_4(M, N + 4, P, T)
#    define CRTP_FRIEND_REPEATER_16(M, N, P, T) CRTP_FRIEND_REPEATER_8(M, N, P, T) CRTP_FRIEND_REPEATER_8(M, N + 8, P, T)
#    define CRTP_FRIEND_REPEATER_32(M, N, P, T) CRTP_FRIEND_REPEATER_16(M, N, P, T) CRTP_FRIEND_REPEATER_16(M, N + 16, P, T)
#    define CRTP_FRIEND_REPEATER_64(M, N, P, T) CRTP_FRIEND_REPEATER_32(M, N, P, T) CRTP_FRIEND_REPEATER_32(M, N + 32, P, T)
#    define CRTP_FRIEND_REPEATER_128(M, N, P, T) CRTP_FRIEND_REPEATER_64(M, N, P, T) CRTP_FRIEND_REPEATER_64(M, N + 64, P, T)

#    define CRTP_FRIEND_N(N, P, T) \
        friend std::tuple_element_t<std::min(static_cast<std::size_t>(N + 1), sizeof...(P)), std::tuple<void, T...>>;

#    define CRTP_VARIADIC_FRIEND(P, T) CRTP_FRIEND_REPEATER_128(CRTP_FRIEND_N, 0, P, T)

#endif // CRTP_VARIADIC_FRIEND

/*
 * Helper macro for be more expressive
 */
#ifndef CRTP_FRIEND

// T - Type
#    define CRTP_FRIEND(T) friend T;

#endif // CRTP_FRIEND

#endif // MARKLAR_DETAIL_CRTP_MACRO_HPP
