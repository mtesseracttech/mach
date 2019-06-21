//
// Created by mtesseract on 6/4/19.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"
#ifndef MACH_VECTOR3_HPP
#define MACH_VECTOR3_HPP

#include "Vector.hpp"

namespace mach {
    template<typename T>
    class Vector3 final : public Vector<Vector3<T>, T, 3> {
    public:
        union {
            std::array<T, 3> m_array;
            struct {
                T x, y, z;
            };
        };

        Vector3() : m_array{0} {}

        explicit Vector3(T p_s) : m_array{p_s} {}

        Vector3(T p_x, T p_y, T p_z) : m_array{p_x, p_y, p_z} {}

        template<typename... Args, typename = typename std::enable_if<sizeof...(Args) == 3>::type>
        explicit Vector3(Args &&... p_values) : m_array{std::forward<Args>(p_values)...} {}


        T &operator[](size_t p_n) { return m_array[p_n]; }

        const T &operator[](size_t p_n) const { return m_array[p_n]; }

        static inline Vector3 cross(const Vector3 &p_v1, const Vector3 &p_v2) {
            Vector3 output(
                    p_v1.y * p_v2.z - p_v1.z * p_v2.y,
                    p_v1.z * p_v2.x - p_v1.x * p_v2.z,
                    p_v1.x * p_v2.y - p_v1.y * p_v2.x
            );
            return output;
        }

        inline Vector3 cross(const Vector3 &p_v) {
            return cross(*this, p_v);
        }
    };
}

#endif //MACH_VECTOR3_HPP

#pragma clang diagnostic pop