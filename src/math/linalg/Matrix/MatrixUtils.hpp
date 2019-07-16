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
	Matrix4 <T>
	view(const Vector3 <T> &p_position, const Vector3 <T> &p_right, const Vector3 <T> &p_up,
	     const Vector3 <T> &p_direction) {
		mach_assert(p_right.is_unit(), "Right vector needs to be unit");
		mach_assert(p_up.is_unit(), "Up vector needs to be unit");
		mach_assert(p_direction.is_unit(), "Direction vector needs to be unit");

		Matrix4<T> direction(p_right.x, p_up.x, p_direction.x, 0.0,
		                     p_right.y, p_up.y, p_direction.y, 0.0,
		                     p_right.z, p_up.z, p_direction.z, 0.0,
		                     0.0, 0.0, 0.0, 1.0);

		Matrix4<T> position(1.0, 0.0, 0.0, 0.0,
		                    0.0, 1.0, 0.0, 0.0,
		                    0.0, 0.0, 1.0, 0.0,
		                    -p_position.x, -p_position.y, -p_position.z, 1.0);
		return direction * position;
	}

	template<typename T>
	Matrix4 <T> look_at(const Vector3 <T> &p_origin, const Vector3 <T> &p_target, const Vector3 <T> &p_up) {
		Vector3<T> forward = (p_target - p_origin).normalized();
		Vector3<T> right = Vector3<T>::cross(forward, p_up).normalized();
		Vector3<T> up = Vector3<T>::cross(right, forward).normalized();
		return view(p_origin, right, up, forward);
	}

	template<typename T>
	Matrix4 <T>
	compose_trs(const Vector3 <T> &p_position, const Quaternion <T> &p_rotation, const Vector3 <T> &p_scale) {
		return translate(p_position) *
		       RotationMatrix<T>::from_quat(p_rotation).to_mat4() *
		       ScaleMatrix<T>::scale_along_cardinal_axes(p_scale).to_mat4();
	}

	template<typename T>
	Matrix4 <T>
	compose_trs(const Vector3 <T> &p_position, const RotationMatrix <T> &p_rotation, const Vector3 <T> &p_scale) {
		return translate(p_position) *
		       p_rotation.to_mat4() *
		       ScaleMatrix<T>::scale_along_cardinal_axes(p_scale).to_mat4();
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
		*p_rotation = Quaternion<T>::from_matrix(rotation);
	}

	template<typename T>
	void decompose_trs(const Matrix4 <T> p_trs_matrix,
	                   Vector3 <T> *p_translation,
	                   RotationMatrix <T> *p_rotation,
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
		*rotation = RotationMatrix<T>::from_mat3(rotation);
	}

	template<typename T>
	Matrix4 <T> perspective(const T &p_z_near, const T &p_z_far, const T &p_fov_y, const T &p_aspect_ratio) {
		mach_assert(p_z_near > 0.0, "Near clipping distance must be positive");
		mach_assert(p_z_far > p_z_near, "Far clipping distance must further than the near clipping distance");
		T fov_x = p_aspect_ratio * p_fov_y;
		return Matrix4<T>(p_z_near / fov_x, 0.0, 0.0, 0.0,
		                  0.0, p_z_near / p_fov_y, 0.0, 0.0,
		                  0.0, 0.0, -(p_z_far + p_z_near) / (p_z_far - p_z_near),
		                  (-2.0 * p_z_far * p_z_near) / (p_z_far - p_z_near),
		                  0.0, 0.0 - 1.0, 0.0);
	}

	template<typename T>
	Matrix4 <T>
	perspective_assym(const T &p_z_near, const T &p_z_far, const T &p_top, const T &p_bottom, const T &p_left,
	                  const T &p_right) {
		mach_assert(p_z_near > 0.0, "Near clipping distance must be positive");
		mach_assert(p_z_far > p_z_near, "Far clipping distance must further than the near clipping distance");
		return Matrix4<T>(2.0 * p_z_near / p_right - p_left, 0.0, (p_right + p_left) / (p_right - p_left), 0.0,
		                  0.0, 2.0 * p_z_near / p_top - p_bottom, (p_top + p_bottom) / (p_top - p_bottom), 0.0,
		                  0.0, 0.0, -(p_z_far + p_z_near) / (p_z_far - p_z_near),
		                  (2.0 * p_z_far * p_z_near) / (p_z_far - p_z_near),
		                  0.0, 0.0, -1.0, 0.0);
	}

	template<typename T>
	Matrix4 <T> orthographic(T p_z_near, T p_z_far, T p_fov_y, T p_aspect_ratio) {
		T fov_x = p_aspect_ratio * p_fov_y;
		mach_assert(p_z_near > 0.0, "Near clipping distance must be positive");
		mach_assert(p_z_far > p_z_near, "Far clipping distance must further than the near clipping distance");
		return Matrix4<T>(1.0 / fov_x, 0.0, 0.0, 0.0,
		                  0.0, 1.0 / p_fov_y, 0.0, 0.0,
		                  0.0, 0.0, -2.0 / (p_z_far - p_z_near), -(p_z_far + p_z_near) / (p_z_far - p_z_near),
		                  0.0, 0.0, 0.0, 1.0);
	}

	template<typename T>
	Matrix4 <T> orthographic_assymetric(T p_z_near, T p_z_far, T p_left, T p_right, T p_top, T p_bottom) {
		mach_assert(p_z_near > 0.0, "Near clipping distance must be positive");
		mach_assert(p_z_far > p_z_near, "Far clipping distance must further than the near clipping distance");
		return Matrix4<T>(2.0 / (p_right - p_left), 0.0, 0.0, -(p_right + p_left) / (p_right - p_left),
		                  0.0, 2.0 / (p_top - p_bottom), 0.0, -(p_top + p_bottom) / (p_top - p_bottom),
		                  0.0, 0.0, -2.0 / (p_z_far - p_z_near), -(p_z_far + p_z_near) / (p_z_far - p_z_near),
		                  0.0, 0.0, 0.0, 1.0);
	}
}

#endif //MACH_MATRIXUTILS_HPP
