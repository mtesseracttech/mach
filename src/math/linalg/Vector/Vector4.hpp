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

		Vector4(T p_x, T p_y, T p_z, T p_w) : m_array{p_x, p_y, p_z, p_w} {}

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
