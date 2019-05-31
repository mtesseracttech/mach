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


namespace mach {
	template<typename T, std::size_t N>
	class Vector {
	public:
		virtual T &operator[](size_t p_n) {};

		virtual const T &operator[](size_t p_n) const {};

		size_t size() {
			return N;
		}

		friend std::ostream &operator<<(std::ostream &p_os, const Vector<T, N> &p_v) {
			p_os << std::fixed << std::setprecision(4) << '(';
			for (size_t i = 0; i < N - 1; i++) {
				p_os << p_v[i] << ',';
			}
			p_os << p_v[N - 1] << ')';
			return p_os;
		};


		T dot(const Vector<T, N> &p_v) {
			return dot(*this, p_v);
		}

		static T dot(const Vector<T, N> &p_v1, const Vector<T, N> &p_v2) {
			T d = 0.0;
			for (size_t i = 0; i < N; ++i) {
				d += p_v1[i] * p_v2[i];
			}
			return d;
		}


		T length_squared() {
			return dot(*this);
		}

		T length() {
			return std::sqrt(length_squared());
		}

		static T distance(const Vector<T, N> &p_v0, const Vector<T, N> &p_v1) {
			Vector<T, N> v_d = p_v1 - p_v0;
			return v_d.length();
		}

		Vector operator+(const Vector<T, N> &p_v) {
			Vector<T, N> output;
			for (size_t i = 0; i < size(); i++) {
				output[i] = (*this)[i] + p_v[i];
			}
			return output;
		}

		Vector operator-(const Vector<T, N> &p_v) {
			Vector<T, N> output;
			for (size_t i = 0; i < size(); i++) {
				output[i] = (*this)[i] - p_v[i];
			}
			return output;
		}

		Vector operator*(const Vector<T, N> &p_v) {
			Vector<T, N> output;
			for (size_t i = 0; i < size(); i++) {
				output[i] = (*this)[i] * p_v[i];
			}
			return output;
		}

		Vector operator/(const Vector<T, N> &p_v) {
			Vector<T, N> output;
			for (size_t i = 0; i < size(); i++) {
				output[i] = (*this)[i] / p_v[i];
			}
			return output;
		}
	};
}
#endif //MACH_VECTOR_HPP
