//
// Created by mtesseract on 7/5/19.
//

#ifndef MACH_MATRIXUTILS_HPP
#define MACH_MATRIXUTILS_HPP

#include <math/linalg/LinAlgTypes.hpp>
#include "RotationMatrix.hpp"
#include "ScaleMatrix.hpp"

namespace mach::math {

	template<typename T>
	Matrix4 <T> translate(const Vector3 <T> &p_trans) {
		return Matrix4<T>(1.0, 0.0, 0.0, 0.0,
		                  0.0, 1.0, 0.0, 0.0,
		                  0.0, 0.0, 1.0, 0.0,
		                  p_trans.x, p_trans.y, p_trans.z, 1.0);
	}

	template<typename T>
	void decompose_trs(const Matrix4 <T> p_trs_matrix,
	                   Vector3 <T> *p_translation,
	                   Quaternion <T> *p_rotation,
	                   Vector3 <T> *p_scale) {
		p_scale->x = Vector3<T>(p_trs_matrix[0]).length();
		p_scale->y = Vector3<T>(p_trs_matrix[1]).length();
		p_scale->z = Vector3<T>(p_trs_matrix[2]).length();

		p_translation->x = p_trs_matrix[3].x;
		p_translation->y = p_trs_matrix[3].y;
		p_translation->z = p_trs_matrix[3].z;

		Matrix3<T> rotation;
		rotation[0] = Vector3<T>(p_trs_matrix[0] / p_scale->x);
		rotation[1] = Vector3<T>(p_trs_matrix[1] / p_scale->y);
		rotation[2] = Vector3<T>(p_trs_matrix[2] / p_scale->z);

		//Logger::log(p_trs_matrix);

		*p_rotation = Quaternion<T>::from_matrix(rotation);

		//Logger::log(*p_translation);
		//Logger::log(*p_rotation);
		//Logger::log(*p_scale);
		//Logger::log(p_trs_matrix);
	}

	template<typename T>
	Matrix4 <T> perspective(const T &p_near, const T &p_far, const T &p_fov_y, const T &p_aspect_ratio) {
		T fov_x = p_aspect_ratio * p_fov_y;
		return Matrix4<T>(p_near / fov_x, 0.0, 0.0, 0.0,
		                  0.0, p_near / p_fov_y, 0.0, 0.0,
		                  0.0, 0.0, -(p_far + p_near) / (p_far - p_near), (-2.0 * p_far * p_near) / (p_far - p_near),
		                  0.0, 0.0 - 1.0, 0.0);
	}

	template<typename T>
	Matrix4 <T>
	perspective_assym(const T &p_z_near, const T &p_z_far, const T &p_top, const T &p_bottom, const T &p_left,
	                  const T &p_right) {
		return Matrix4<T>(2.0 * p_z_near / p_right - p_left, 0.0, (p_right + p_left) / (p_right - p_left), 0.0,
		                  0.0, 2.0 * p_z_near / p_top - p_bottom, (p_top + p_bottom) / (p_top - p_bottom), 0.0,
		                  0.0, 0.0, -(p_z_far + p_z_near) / (p_z_far - p_z_near),
		                  (2.0 * p_z_far * p_z_near) / (p_z_far - p_z_near),
		                  0.0, 0.0, -1.0, 0.0);
	}

	template<typename T>
	Matrix4 <T> orthographic(T p_z_near, T p_z_far, T p_fov_y, T p_aspect_ratio) {
		T fov_x = p_aspect_ratio * p_fov_y;
		return Matrix4<T>(1.0 / fov_x, 0.0, 0.0, 0.0,
		                  0.0, 1.0 / p_fov_y, 0.0, 0.0,
		                  0.0, 0.0, -2.0 / (p_z_far - p_z_near), -(p_z_far + p_z_near) / (p_z_far - p_z_near),
		                  0.0, 0.0, 0.0, 1.0);
	}

	template<typename T>
	Matrix4 <T> orthographic_assymetric(T p_z_near, T p_z_far, T p_left, T p_right, T p_top, T p_bottom) {
		return Matrix4<T>(2.0 / (p_right - p_left), 0.0, 0.0, -(p_right + p_left) / (p_right - p_left),
		                  0.0, 2.0 / (p_top - p_bottom), 0.0, -(p_top + p_bottom) / (p_top - p_bottom),
		                  0.0, 0.0, -2.0 / (p_z_far - p_z_near), -(p_z_far + p_z_near) / (p_z_far - p_z_near),
		                  0.0, 0.0, 0.0, 1.0);
	}
}

#endif //MACH_MATRIXUTILS_HPP
