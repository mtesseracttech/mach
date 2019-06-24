//
// Created by mtesseract on 6/11/19.
//

#ifndef MACH_ROTATIONMATRIX_HPP
#define MACH_ROTATIONMATRIX_HPP

#include <math/linalg/Quaternion.hpp>
#include <math/linalg/Vector/Vector3.hpp>
#include <math/linalg/Vector/Vector4.hpp>
#include <auxiliary/exceptions/NotImplemented.hpp>
#include "Matrix.hpp"


namespace mach {
	template<typename T>
	class RotationMatrix {
		using Mat3 = Matrix<Vector3<T>, Vector3<T>, T, 3, 3>;
		using Mat4 = Matrix<Vector4<T>, Vector4<T>, T, 4, 4>;


		Mat3 m_matrix;

		explicit RotationMatrix(Mat3 p_matrix) : m_matrix(p_matrix) {}

		template<typename... Args, typename = typename std::enable_if<sizeof...(Args) == 9>::type>
		explicit RotationMatrix(Args &&... p_values) : m_matrix(static_cast<T>(std::forward<Args>(p_values))...) {}

	public:

		RotationMatrix() : m_matrix(Mat3::identity()) {}

		template<RotationOrder O = BPH>
		inline static RotationMatrix from_euler(const EulerAngles<T, O> &p_angles) {
			T sp = std::sin(p_angles.pitch);
			T cp = std::cos(p_angles.pitch);
			T sh = std::sin(p_angles.heading);
			T ch = std::cos(p_angles.heading);
			T sb = std::sin(p_angles.bank);
			T cb = std::cos(p_angles.bank);

			Mat3 b(cb, sb, 0.0,
			       -sb, cb, 0.0,
			       0.0, 0.0, 1.0);
			Mat3 h(ch, 0.0, -sh,
			       0.0, 1.0, 0.0,
			       sh, 0.0, ch);
			Mat3 p(1.0, 0.0, 0.0,
			       0.0, cp, sp,
			       0.0, -sp, cp);

			RotationMatrix result;
			result.m_matrix = combine_rotations<O>(p, h, b);
			return result;
		}

		inline RotationMatrix from_quat(const Quaternion<T> &p_q) {
			return RotationMatrix(1.0 - 2.0 * p_q.y * p_q.y - 2.0 * p_q.z * p_q.z,
			                      2.0 * p_q.x * p_q.y + 2.0 * p_q.w * p_q.z,
			                      2.0 * p_q.x * p_q.z - 2.0 * p_q.w * p_q.y,
			                      2.0 * p_q.x * p_q.y - 2.0 * p_q.w * p_q.z,
			                      1.0 - 2.0 * p_q.x * p_q.x - 2.0 * p_q.z * p_q.z,
			                      2.0 * p_q.y * p_q.z + 2.0 * p_q.w * p_q.x,
			                      2.0 * p_q.x * p_q.z + 2.0 * p_q.w * p_q.y,
			                      2.0 * p_q.y * p_q.z - 2.0 * p_q.w * p_q.x,
			                      1.0 - 2.0 * p_q.x * p_q.x - 2.0 * p_q.y * p_q.y);
		}

		//Angle Axis
		inline static RotationMatrix from_angle_axis(T p_theta, const Vector3<T> &p_n) {
			mach_assert(p_n.is_unit(),
			            "You can only construct a RotationMatrix from an angle-axis with a normalized axis");
			T c = std::cos(p_theta);
			T s = std::sin(p_theta);
			T o_m_c = 1.0 - c;
			return RotationMatrix(p_n.x * p_n.x * o_m_c + c,
			                      p_n.x * p_n.y * o_m_c + p_n.z * s,
			                      p_n.x * p_n.z * o_m_c - p_n.y * s,
			                      p_n.x * p_n.y * o_m_c - p_n.z * s,
			                      p_n.y * p_n.y * o_m_c + c,
			                      p_n.y * p_n.z * o_m_c + p_n.x * s,
			                      p_n.x * p_n.z * o_m_c + p_n.y * s,
			                      p_n.y * p_n.z * o_m_c - p_n.x * s,
			                      p_n.z * p_n.z * o_m_c + c
			);

		}

		//Angle Axis
		inline static RotationMatrix from_angle_axis(const AngleAxis<T> &p_angle_axis) {
			return from_angle_axis(p_angle_axis.theta, p_angle_axis.n);
		}


		inline RotationMatrix transpose() {
			RotationMatrix matrix(m_matrix.transpose());
			return matrix;
		}

		//Happens to be the same as the transpose for rotation matrices
		inline RotationMatrix inverse() {
			return transpose();
		}

		template<RotationOrder O = BPH>
		inline RotationMatrix rotate(const RotationMatrix &p_m) {
			m_matrix *= p_m.m_matrix;
		}

		inline RotationMatrix rotate(const RotationMatrix &p_m) {
			m_matrix *= p_m.m_matrix;
		}

		inline RotationMatrix rotate(const Quaternion<T> &p_q) {
			m_matrix *= RotationMatrix(p_q);
		}

		inline Mat4 to_mat4() const {
			Mat4 result(m_matrix[0][0], m_matrix[0][1], m_matrix[0][2], 0.0,
			            m_matrix[1][0], m_matrix[1][1], m_matrix[1][2], 0.0,
			            m_matrix[2][0], m_matrix[2][1], m_matrix[2][2], 0.0,
			            0.0, 0.0, 0.0, 1.0);
			return result;
		}

		inline Vector3<T> right() {
			return m_matrix[0];
		}

		inline Vector3<T> up() {
			return m_matrix[1];
		}

		inline Vector3<T> forward() {
			return m_matrix[2];
		}

		inline Vector3<T> left() {
			return -m_matrix[0];
		}

		inline Vector3<T> down() {
			return -m_matrix[1];
		}

		inline Vector3<T> back() {
			return -m_matrix[2];
		}
	};
}

#endif //MACH_ROTATIONMATRIX_HPP
