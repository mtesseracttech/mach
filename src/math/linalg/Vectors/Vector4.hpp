//
// Created by mtesseract on 6/4/19.
//

#ifndef MACH_VECTOR4_HPP
#define MACH_VECTOR4_HPP

#include "Vector.hpp"

namespace mach {
    template<typename T>
    class Vector4 final : public Vector<Vector4<T>, T, 4> {
    public:
        union {
            std::array<T, 4> m_array;
            struct {
                T x, y, z, w;
            };
        };

        Vector4() : x(0), y(0), z(0), w(0) {}

        Vector4(T p_s) : x(p_s), y(p_s), z(p_s), w(p_s) {}

        Vector4(T p_x, T p_y, T p_z, T p_w) : x(p_x), y(p_y), z(p_z), w(p_w) {}

        T &operator[](size_t p_n) override { return m_array[p_n]; }

        const T &operator[](size_t p_n) const override { return m_array[p_n]; }
    };


}

#endif //MACH_VECTOR4_HPP
