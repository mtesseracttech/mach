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
#include "auxiliary/MachAssertion.hpp"

/*
 * Thanks to Gaztin from the Cherno discord, for helping me with the CRTP and the functor system.
 */

namespace mach {
	template<typename Base, typename T, size_t N>
	class Vector {
	public:
		constexpr size_t size() { return N; }

		static constexpr Base zero() {
			return Base(0.0);
		}

		static constexpr Base one() {
			return Base(1.0);
		}

	private:
		//Replacements for the index operators, to avoid problems in the subclasses
		inline T &get_n(size_t p_n) {
			return (*reinterpret_cast<const Base *>(this))[p_n];
		}

		const T &get_n(size_t p_n) const {
			return (*reinterpret_cast<const Base *>(this))[p_n];
		}

	protected:

		//Member-wise
		template<typename Functor>
		inline Base un_op(Functor &&p_op) const {
			Base output;
			for (size_t i = 0; i < N; ++i) {
				output[i] = p_op(get_n(i));
			}
			return output;
		}

		template<typename Functor>
		inline Base bin_op(const Base &p_v, Functor &&p_op) const {
			Base output;
			for (size_t i = 0; i < N; ++i) {
				output[i] = p_op(get_n(i), p_v[i]);
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

		friend inline Base operator*(const T &p_s, const Base &p_v) {
			return p_v * p_s;
		}

		inline bool operator==(const Base &p_v) const {
			for (size_t i = 0; i < N; ++i) {
				if (!approx_eq<T>(get_n(i), p_v[i])) {
					return false;
				}
			}
			return true;
		}

		friend std::ostream &operator<<(std::ostream &p_os, const Base &p_v) {
			p_os << std::fixed << std::setprecision(3) << "(" << p_v[0];
			for (int i = 1; i < N; ++i) {
				p_os << "," << p_v[i];
			}
			p_os << ")";
			return p_os;
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
			return approx_eq<T>(length_squared(), 1.0);
		}

		inline Base normalized() const {
			return (*this) / length();
		}

		inline void normalize() const {
			T length = length();

		}

		static inline Base reflect(const Base &p_incident, const Base &p_normal) {
			mach_assert(p_normal.is_unit(), "The reflect function only works with normalized normal vectors");
			return p_incident - static_cast<T>(2.0) * dot(p_incident, p_normal) * p_normal;
		}

		static inline Base refract(const Base &p_incident, const Base &p_normal, const T p_eta) {
			mach_assert(p_normal.is_unit(), "The refraction function only works with normalized normal vectors");
			T n_dot_i = dot(p_normal, p_incident);
			T k = 1.0 - p_eta * p_eta * (1.0 - n_dot_i * n_dot_i);
			if (k < 0.0) {
				return zero();
			} else {
				return p_eta * p_incident - (p_eta * n_dot_i * std::sqrt(k)) * p_normal;
			}
		}

		static inline Base mix(const Base &p_start, const Base &p_end, T p_t) {
			return p_start + (p_end - p_start) * p_t;
		}

		static inline Base mix(const Base &p_start, const Base &p_end, const Base &p_t) {
			Base result;
			Base delta = p_end - p_start;
			for (size_t i = 0; i < N; ++i) {
				result[i] = p_start[i] + delta[i] * p_t;
			}
			return result;
		}

		static inline Base clamp(const Base &p_v, const T p_low, const T p_high) {
			Base result;
			for (size_t i = 0; i < N; ++i) {
				result[i] = std::clamp(p_v[i], p_low, p_high);
			}
			return result;
		}

		static inline Base clamp(const Base &p_v, const Base &p_low, const Base &p_high) {
			Base result;
			for (size_t i = 0; i < N; ++i) {
				result[i] = std::clamp(p_v[i], p_low[i], p_high[i]);
			}
			return result;
		}

		inline T get_largest() const {
			T largest = get_n(0);
			for (size_t i = 1; i < N; ++i) {
				if (get_n(i) > largest) largest = get_n(i);
			}
			return largest;
		}

		inline T get_smallest() const {
			T smallest = get_n(0);
			for (size_t i = 1; i < N; ++i) {
				if (get_n(i) < smallest) smallest = get_n(i);
			}
			return smallest;
		}

		inline size_t get_largest_index() const {
			size_t largest = 0;
			for (size_t i = 1; i < N; ++i) {
				if (get_n(i) > largest) largest = i;
			}
			return largest;
		}

		inline size_t get_smallest_index() const {
			size_t smallest = 0;
			for (size_t i = 1; i < N; ++i) {
				if (get_n(i) < smallest) smallest = i;
			}
			return smallest;
		}
	};
}
#endif //MACH_VECTOR_HPP
