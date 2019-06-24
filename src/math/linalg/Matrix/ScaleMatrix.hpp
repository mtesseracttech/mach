//
// Created by mtesseract on 6/24/19.
//

#ifndef MACH_SCALEMATRIX_HPP
#define MACH_SCALEMATRIX_HPP

#include <math/linalg/Vector/Vector3.hpp>
#include <math/linalg/Vector/Vector4.hpp>
#include <auxiliary/exceptions/NotImplemented.hpp>
#include "Matrix.hpp"

namespace mach {
	template<typename T>
	class ScaleMatrix {
		using Mat3 = Matrix<Vector3<T>, Vector3<T>, T, 3, 3>;
		using Mat4 = Matrix<Vector4<T>, Vector4<T>, T, 4, 4>;

		Mat3 m_matrix;

		explicit ScaleMatrix(Mat3 p_matrix) : m_matrix(p_matrix) {}

		template<typename... Args, typename = typename std::enable_if<sizeof...(Args) == 9>::type>
		explicit ScaleMatrix(Args &&... p_values) : m_matrix(static_cast<T> (std::forward<Args>(p_values))...) {}

	public:

		inline static ScaleMatrix uniform_scale(T p_s) {
			return ScaleMatrix(p_s, 0.0, 0.0,
			                   0.0, p_s, 0.0,
			                   0.0, 0.0, p_s);
		}

		inline static ScaleMatrix scale_along_cardinal_axes(const Vector3<T> &p_k) {
			return ScaleMatrix(p_k.x, 0.0, 0.0,
			                   0.0, p_k.y, 0.0,
			                   0.0, 0.0, p_k.z);
		}

		inline static ScaleMatrix scale_along_direction(const Vector3<T> &p_n, T p_k) {
			mach_assert(p_n.is_unit(),
			            "You can only create a scale matrix along a normalized vector");
			T km = p_k - 1.0;
			return ScaleMatrix(1.0 + km * p_n.x * p_n.x, km * p_n.x * p_n.y, km * p_n.x, *p_n.z,
			                   km * p_n.x * p_n.y, 1.0 + km * p_n.y * p_n.y, km * p_n.y, *p_n.z,
			                   km * p_n.x, *p_n.z, km * p_n.y, *p_n.z, 1.0 + km * p_n.z * p_n.z);
		}

		inline Mat4 to_mat4() const {
			Mat4 result(m_matrix[0][0], m_matrix[0][1], m_matrix[0][2], 0.0,
			            m_matrix[1][0], m_matrix[1][1], m_matrix[1][2], 0.0,
			            m_matrix[2][0], m_matrix[2][1], m_matrix[2][2], 0.0,
			            0.0, 0.0, 0.0, 1.0);
			return result;
		}
	};
}

#endif //MACH_SCALEMATRIX_HPP
