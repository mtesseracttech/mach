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

        Vector2() : x(0), y(0) {}

        Vector2(T p_s) : x(p_s), y(p_s) {}

        Vector2(T p_x, T p_y) : x(p_x), y(p_y) {}

        T &operator[](size_t p_n) override { return m_array[p_n]; }

        const T &operator[](size_t p_n) const override { return m_array[p_n]; }
    };
}


#endif //MACH_VECTOR2_HPP
