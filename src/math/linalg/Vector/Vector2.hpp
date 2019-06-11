//
// Created by mtesseract on 6/4/19.
//

#ifndef MACH_VECTOR2_HPP
#define MACH_VECTOR2_HPP

#include "Vector.hpp"

namespace mach {
    template<typename T>
    class Vector2 final : public Vector<Vector2<T>, T, 2> {
    public:
        union {
            std::array<T, 2> m_array;
            struct {
                T x, y;
            };
        };

        Vector2() : m_array{0} {}

        explicit Vector2(T p_s) : m_array{p_s} {}

        Vector2(T p_x, T p_y) : m_array{p_x, p_y} {}

        template<typename... Args, typename = typename std::enable_if<sizeof...(Args) == 2>::type>
        explicit Vector2(Args &&... p_values) : m_array{std::forward<Args>(p_values)...} {}

        T &operator[](size_t p_n) { return m_array[p_n]; }

        const T &operator[](size_t p_n) const { return m_array[p_n]; }
    };
}


#endif //MACH_VECTOR2_HPP
