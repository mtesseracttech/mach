//
// Created by mtesseract on 6/9/19.
//

#ifndef MACH_QUATERNION_HPP
#define MACH_QUATERNION_HPP

#include "Vector/Vector3.hpp"
#include "Rotations.hpp"

namespace mach {
    template<typename T>
    class Quaternion {
    public:
        union {
            struct {
                T w;
                struct {
                    T x, y, z;
                    Vector3<T> v;
                };

            };
            struct {
                std::array<T, 4> m_array;
            };
        };

        Quaternion(T p_w, T p_x, T p_y, T p_z) : m_array{p_w, p_x, p_y, p_z} {}

        Quaternion(T p_w, Vector3<T> p_v) : w(p_w), v(p_v) {}

        template<typename... Args, typename = typename std::enable_if<sizeof...(Args) == 3>::type>
        Quaternion(T p_w, Args &&... p_values) : w(p_w), v(std::forward<Args>(p_values)...) {}


        static constexpr Quaternion identity() {
            return Quaternion(1.0, 0.0, 0.0, 0.0);
        }

        inline Quaternion operator*(const Quaternion &p_q) const {
            Quaternion output;
            output.w = w * p_q.w - v.dot(p_q.v);
            output.v = w * p_q.v + p_q.w * p_q.v + (v.cross(p_q.v));
            return output;
        }

        inline Quaternion operator*(const T &p_s) const {
            return Quaternion(w * p_s, v * p_s);
        }

        friend inline Quaternion operator*(T &p_s, const Quaternion &p_q) {
            return p_q * p_s;
        }

        inline T dot(const Quaternion &p_q) const {
            return w + p_q.w + v.dot(p_q.v);
        }

        inline T magnitude_squared() {
            return dot(*this);
        }

        inline T magnitude() {
            return std::sqrt(magnitude_squared());
        }

        inline Quaternion conjugate() {
            return Quaternion(w, -v);
        }

        inline Quaternion inverse() {
            T inv = 1.0 / magnitude();
            return conjugate() * inv;
        }

        inline Quaternion normalized() {
            T inv = 1.0 / magnitude();
            return Quaternion(w * inv, v * inv);
        }

        inline bool is_versor() {
            return approx_eq(magnitude_squared(), 1.0);
        }


        inline Quaternion pow(T p_exp) {
            if (std::abs(w) < 0.9999) {
                T alpha = std::acos(w);
                T new_alpha = alpha * p_exp;
                T scalar = std::sin(new_alpha) / std::sin(alpha);
                return Quaternion(std::cos(new_alpha), v * scalar);
            } else {
                return Quaternion(x, y, z, w);
            }
        }

        inline Quaternion exp() {
            T v_l = v.length();
            if (!approx_eq(v_l, 0.0)) {
                return std::exp(w) * Quaternion(std::cos(w), v / v.length() * sin(v.length()));
            } else {
                return Quaternion::identity();
            }

        }

        inline Quaternion log() {
            T v_l = v.length();
            T q_l = magnitude();
            if (!approx_eq(v_l, 0.0) && !approx_eq(q_l, 0.0)) {
                return Quaternion(std::log(magnitude()), (v / v_l) * std::acos(w / q_l));
            } else {
                return Quaternion::identity();
            }
        }

        inline Quaternion from_euler(const Vector3<T> &p_v) {
            from_euler(p_v.x, p_v.y, p_v.z);
        }

        inline Quaternion from_euler(T p_pitch, T p_heading, T p_bank, RotationOrder p_order = BPH) {
            T half_pitch = p_pitch / 2.0;
            T half_heading = p_heading / 2.0;
            T half_bank = p_bank / 2.0;

            T sp = std::sin(half_pitch);
            T cp = std::cos(half_pitch);
            T sh = std::sin(half_heading);
            T ch = std::cos(half_heading);
            T sb = std::sin(half_bank);
            T cb = std::cos(half_bank);

            Quaternion p = Quaternion(cp, sp, 0.0, 0.0);
            Quaternion h = Quaternion(ch, 0.0, sh, 0.0);
            Quaternion b = Quaternion(cb, 0.0, 0.0, sb);

            switch (p_order) {
                case PHB:
                    return p * h * b;
                case PBH:
                    return p * b * h;
                case HPB:
                    return h * p * b;
                case HBP:
                    return h * b * p;
                case BPH:
                    return b * p * h;
                case BHP:
                    return b * h * p;
            }
        }

        inline Quaternion from_angle_axis(T p_t, const Vector3<T> &p_v) {
            assert(p_v.is_unit());
            T st = std::sin(p_t / 2.0);
            T ct = std::cos(p_t / 2.0);
            Quaternion(ct, p_v * st);
        }


    };
}

#endif //MACH_QUATERNION_HPP
