//
// Created by mtesseract on 6/11/19.
//

#ifndef MACH_ROTATIONMATRIX_HPP
#define MACH_ROTATIONMATRIX_HPP

#include <math/linalg/Quaternion.hpp>
#include "Matrix.hpp"
#include "../Vector/Vector3.hpp"
#include "auxiliary/Exceptions.hpp"

namespace mach {
    template<typename T>
    class RotationMatrix {
    private: //This ought to be private, to preserve the validity of the other statements
        using Mat3 = Matrix<Vector3<T>, Vector3<T>, T, 3, 3>;

        Mat3 m_matrix;

        RotationMatrix(Mat3 p_matrix) : m_matrix(p_matrix) {}

    public:

        inline RotationMatrix transpose() {
            RotationMatrix matrix(m_matrix.transpose());
            return matrix;
        }

        inline RotationMatrix inverse() { //Happens to be the same as the transpose for rotation matrices
            return transpose();
        }

        inline RotationMatrix from_quat(const Quaternion<T> p_q) {
            throw NotImplemented();
        }


    };
}

#endif //MACH_ROTATIONMATRIX_HPP
