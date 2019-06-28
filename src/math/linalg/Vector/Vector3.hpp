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

		explicit Vector3(T p_s) : m_array{p_s, p_s, p_s} {}

		Vector3(const Vector3 &p_v) : x(p_v.x), y(p_v.y), z(p_v.z) {}

		Vector3(T p_x, T p_y, T p_z) : x(p_x), y(p_y), z(p_z) {}

		Vector3 &operator=(const Vector3 &p_rhs) {
			if (this == &p_rhs) return *this;
			x = p_rhs.x;
			y = p_rhs.y;
			z = p_rhs.z;
			return *this;
		}

		T &operator[](size_t p_n) { return m_array[p_n]; }

		const T &operator[](size_t p_n) const { return m_array[p_n]; }

		static constexpr Vector3 right() {
			return Vector3(1, 0, 0);
		}

		static constexpr Vector3 up() {
			return Vector3(0, 1, 0);
		}

		static constexpr Vector3 forward() {
			return Vector3(0, 0, 1);
		}

		static inline Vector3 cross(const Vector3 &p_v1, const Vector3 &p_v2) {
			Vector3 output(
					p_v1.y * p_v2.z - p_v1.z * p_v2.y,
					p_v1.z * p_v2.x - p_v1.x * p_v2.z,
					p_v1.x * p_v2.y - p_v1.y * p_v2.x
			);
			return output;
		}

		inline Vector3 cross(const Vector3 &p_v) const {
			return cross(*this, p_v);
		}
	};
}

#endif //MACH_VECTOR3_HPP

#pragma clang diagnostic pop