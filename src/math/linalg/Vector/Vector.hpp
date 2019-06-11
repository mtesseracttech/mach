//
// Created by mtesseract on 28-5-19.
//

#ifndef MACH_VECTOR_HPP
#define MACH_VECTOR_HPP

#include <array>
#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include "../../util/NumberTraits.hpp"

/*
 * Thanks to Gaztin from the Cherno discord, for helping me with the template code and the functor system.
 */

namespace mach {
    template<typename Base, typename T, size_t N>
    class Vector {
    public:
        constexpr size_t size() { return N; }

        // These 2 operators should not be virtual, no matter how much the impl classes complain
        T &operator[](size_t p_n) {
            return (*reinterpret_cast<const Base *>(this))[p_n];
        }

        const T &operator[](size_t p_n) const {
            return (*reinterpret_cast<const Base *>(this))[p_n];
        }

    protected:

        //Member-wise
        template<typename Functor>
        inline Base un_op(Functor &&p_op) const {
            Base output;
            for (size_t i = 0; i < N; ++i) {
                output[i] = p_op((*reinterpret_cast<const Base *>(this))[i]);
            }
            return output;
        }

        template<typename Functor>
        inline Base bin_op(const Base &p_v, Functor &&p_op) const {
            Base output;
            for (size_t i = 0; i < N; ++i) {
                output[i] = p_op(((*reinterpret_cast<const Base *>(this))[i]), p_v[i]);
            }
            return output;
        }

        //Member/scalar
        template<typename Functor>
        inline Base bin_op(const T &p_s, Functor &&p_op) const {
            Base output;
            for (size_t i = 0; i < N; ++i) {
                output[i] = p_op(((*reinterpret_cast<const Base *>(this))[i]), p_s);
            }
            return output;
        }

    public:
        inline Base operator+(const Base &p_v) const {
            return bin_op(p_v, std::plus<T>());
        }

        inline Base operator-(const Base &p_v) const {
            return bin_op(p_v, std::minus<T>());
        }

        inline Base operator*(const Base &p_v) const {
            return bin_op(p_v, std::multiplies<T>());
        }

        inline Base operator/(const Base &p_v) const {
            return bin_op(p_v, std::divides<T>());
        }

        inline Base operator%(const Base &p_v) const {
            return bin_op(p_v, std::modulus<T>());
        }

        inline Base operator-() const {
            return un_op(std::negate<T>());
        }

        inline Base operator*(const T &p_s) const {
            return bin_op(p_s, std::multiplies<T>());
        }

        inline Base operator/(const T &p_s) const {
            return bin_op(p_s, std::divides<T>());
        }

        inline Base operator%(const T &p_s) const {
            return bin_op(p_s, std::modulus<T>());
        }

        friend inline Base operator*(T &p_s, const Base &p_v) {
            return p_v * p_s;
        }

        inline bool operator==(const Base &p_v) const {
            for (size_t i = 0; i < N; ++i) {
                if (!approx_eq((*this)[i], p_v[i])) {
                    std::cout << "Comparing: " << std::scientific << (*this)[i] << "&" << p_v[i] << std::endl;
                    return false;
                }
            }
            return true;
        }

        friend std::ostream &operator<<(std::ostream &os, const Base &p_v) {
            os << std::fixed << std::setprecision(3) << "(" << p_v[0];
            for (int i = 1; i < N; ++i) {
                os << "," << p_v[i];
            }
            os << ")";
            return os;
        }

        static inline T dot(const Base &p_v1, const Base &p_v2) {
            T result = 0;
            for (size_t i = 0; i < N; ++i) {
                result += p_v1[i] * p_v2[i];
            }
            return result;
        }


        inline T dot(const Base &p_v) const {
            return Vector::dot(*reinterpret_cast<const Base *>(this), p_v);
        }

        inline T length_squared() const {
            return Vector::dot(*reinterpret_cast<const Base *>(this), *reinterpret_cast<const Base *>(this));
        }

        inline T length() const {
            return std::sqrt(length_squared());
        }

        static inline T distance(const Base &p_v1, const Base &p_v2) {
            return (p_v1 - p_v2).length();
        }

        inline bool is_unit() const {
            return approx_eq(length_squared(), 1.0);
        }
    };
}
#endif //MACH_VECTOR_HPP
