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

		Vector4() : m_array{0} {}

		explicit Vector4(T p_s) : m_array{p_s, p_s, p_s, p_s} {}

		Vector4(const Vector4 &p_v) : x(p_v.x), y(p_v.y), z(p_v.z), w(p_v.w) {}

		Vector4(T p_x, T p_y, T p_z, T p_w) : x(p_x), y(p_y), z(p_z), w(p_w) {}

		Vector4 &operator=(const Vector4 &p_rhs) {
			if (this == &p_rhs) return *this;
			x = p_rhs.x;
			y = p_rhs.y;
			z = p_rhs.z;
			w = p_rhs.w;
			return *this;
		}

		T &operator[](size_t p_n) { return m_array[p_n]; }

		const T &operator[](size_t p_n) const { return m_array[p_n]; }

		static constexpr Vector4 right() {
			return Vector4(1, 0, 0, 0);
		}

		static constexpr Vector4 up() {
			return Vector4(0, 1, 0, 0);
		}

		static constexpr Vector4 forward() {
			return Vector4(0, 0, 1, 0);
		}

		static constexpr Vector4 w_only() {
			return Vector4(0, 0, 0, 1);
		}
	};
}

#endif //MACH_VECTOR4_HPP
