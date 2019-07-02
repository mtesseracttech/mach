//
// Created by mtesseract on 6/4/19.
//

#ifndef MACH_LINALGTYPES_HPP
#define MACH_LINALGTYPES_HPP


#include "math/linalg/Matrix/Matrix.hpp"
#include "Quaternion.hpp"

namespace mach {
	template<typename T>
	using Vector2 = Vector<T, 2>;

	template<typename T>
	using Vector3 = Vector<T, 3>;

	template<typename T>
	using Vector4 = Vector<T, 4>;

	//Standard Precision
	typedef Vector2<float> Vec2;
	typedef Vector3<float> Vec3;
	typedef Vector4<float> Vec4;

	//High Precision
	typedef Vector2<double> Vec2h;
	typedef Vector3<double> Vec3h;
	typedef Vector4<double> Vec4h;

	//Signed Integer Precision
	typedef Vector2<int> IVec2;
	typedef Vector3<int> IVec3;
	typedef Vector4<int> IVec4;

	//Unsigned Integer Precision
	typedef Vector2<unsigned int> UVec2;
	typedef Vector3<unsigned int> UVec3;
	typedef Vector4<unsigned int> UVec4;

	//Standard Precision, short form
	typedef Matrix<float, 2, 2> Mat2;
	typedef Matrix<float, 3, 3> Mat3;
	typedef Matrix<float, 4, 4> Mat4;

	//Standard Precision, full form
	typedef Matrix<float, 2, 2> Mat2x2;
	typedef Matrix<float, 2, 3> Mat2x3;
	typedef Matrix<float, 2, 4> Mat2x4;
	typedef Matrix<float, 3, 2> Mat3x2;
	typedef Matrix<float, 3, 3> Mat3x3;
	typedef Matrix<float, 3, 4> Mat3x4;
	typedef Matrix<float, 4, 2> Mat4x2;
	typedef Matrix<float, 4, 3> Mat4x3;
	typedef Matrix<float, 4, 4> Mat4x4;

	//High Precision, short form
	typedef Matrix<double, 2, 2> Mat2h;
	typedef Matrix<double, 3, 3> Mat3h;
	typedef Matrix<double, 4, 4> Mat4h;

	//High Precision, full form
	typedef Matrix<double, 2, 2> Mat2x2h;
	typedef Matrix<double, 2, 3> Mat2x3h;
	typedef Matrix<double, 2, 4> Mat2x4h;
	typedef Matrix<double, 3, 2> Mat3x2h;
	typedef Matrix<double, 3, 3> Mat3x3h;
	typedef Matrix<double, 3, 4> Mat3x4h;
	typedef Matrix<double, 4, 2> Mat4x2h;
	typedef Matrix<double, 4, 3> Mat4x3h;
	typedef Matrix<double, 4, 4> Mat4x4h;

	//Quaternions
	typedef Quaternion<float> Quat;
	typedef Quaternion<double> Quath;
}

#endif //MACH_LINALGTYPES_HPP
