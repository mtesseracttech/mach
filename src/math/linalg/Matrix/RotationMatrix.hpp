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
        using Mat3 = Matrix<Vector3<T>, Vector3<T>, T, 3, 3>;

        Mat3 m_matrix;

        explicit RotationMatrix(Mat3 p_matrix) : m_matrix(p_matrix) {}

    public:

        RotationMatrix() : m_matrix(Mat3::identity()) {}

        template<RotationOrder O = BPH>
        explicit RotationMatrix(const EulerAngles<T, O> &p_angles) {
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

            m_matrix = combine_rotations<O>(p, h, b);
        }

        explicit RotationMatrix(const Quaternion<T> &p_q) {
            m_matrix = {
                    Vector3<T>(1.0 - 2.0 * p_q.y * p_q.y - 2.0 * p_q.z * p_q.z,
                               2.0 * p_q.x * p_q.y + 2.0 * p_q.w * p_q.z,
                               2.0 * p_q.x * p_q.z - 2.0 * p_q.w * p_q.y),
                    Vector3<T>(2.0 * p_q.x * p_q.y - 2.0 * p_q.w * p_q.z,
                               1.0 - 2.0 * p_q.x * p_q.x - 2.0 * p_q.z * p_q.z,
                               2.0 * p_q.y * p_q.z + 2.0 * p_q.w * p_q.x),
                    Vector3<T>(2.0 * p_q.x * p_q.z + 2.0 * p_q.w * p_q.y,
                               2.0 * p_q.y * p_q.z - 2.0 * p_q.w * p_q.x,
                               1.0 - 2.0 * p_q.x * p_q.x - 2.0 * p_q.y * p_q.y)
            };
        }

    public:
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
