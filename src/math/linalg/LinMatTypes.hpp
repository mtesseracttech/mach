//
// Created by mtesseract on 6/4/19.
//

#ifndef MACH_LINMATTYPES_HPP
#define MACH_LINMATTYPES_HPP

#include "math/linalg/Vectors/Vector2.hpp"
#include "math/linalg/Vectors/Vector3.hpp"
#include "math/linalg/Vectors/Vector4.hpp"

#include "math/linalg/Matrices/Matrix.hpp"

namespace mach {
    //Standard Precision
    typedef Vector2<float> Vec2;
    typedef Vector3<float> Vec3;
    typedef Vector4<float> Vec4;

    //High Precision
    typedef Vector2<double> Vec2h;
    typedef Vector3<double> Vec3h;
    typedef Vector4<double> Vec4h;

    //Standard Precision, short form
    typedef Matrix<Vec2, Vec2, float, 2, 2> Mat2;
    typedef Matrix<Vec3, Vec3, float, 3, 3> Mat3;
    typedef Matrix<Vec4, Vec4, float, 4, 4> Mat4;

    //Standard Precision, full form
    typedef Matrix<Vec2, Vec2, float, 2, 2> Mat2x2;
    typedef Matrix<Vec2, Vec3, float, 2, 3> Mat2x3;
    typedef Matrix<Vec2, Vec4, float, 2, 4> Mat2x4;
    typedef Matrix<Vec3, Vec2, float, 3, 2> Mat3x2;
    typedef Matrix<Vec3, Vec3, float, 3, 3> Mat3x3;
    typedef Matrix<Vec3, Vec4, float, 3, 4> Mat3x4;
    typedef Matrix<Vec4, Vec2, float, 4, 2> Mat4x2;
    typedef Matrix<Vec4, Vec3, float, 4, 3> Mat4x3;
    typedef Matrix<Vec4, Vec4, float, 4, 4> Mat4x4;

    //High Precision, short form
    typedef Matrix<Vec2h, Vec2h, double, 2, 2> Mat2h;
    typedef Matrix<Vec3h, Vec3h, double, 3, 3> Mat3h;
    typedef Matrix<Vec4h, Vec4h, double, 4, 4> Mat4h;

    //High Precision, full form
    typedef Matrix<Vec2h, Vec2h, double, 2, 2> Mat2x2h;
    typedef Matrix<Vec2h, Vec3h, double, 2, 3> Mat2x3h;
    typedef Matrix<Vec2h, Vec4h, double, 2, 4> Mat2x4h;
    typedef Matrix<Vec3h, Vec2h, double, 3, 2> Mat3x2h;
    typedef Matrix<Vec3h, Vec3h, double, 3, 3> Mat3x3h;
    typedef Matrix<Vec3h, Vec4h, double, 3, 4> Mat3x4h;
    typedef Matrix<Vec4h, Vec2h, double, 4, 2> Mat4x2h;
    typedef Matrix<Vec4h, Vec3h, double, 4, 3> Mat4x3h;
    typedef Matrix<Vec4h, Vec4h, double, 4, 4> Mat4x4h;
}

#endif //MACH_LINMATTYPES_HPP
