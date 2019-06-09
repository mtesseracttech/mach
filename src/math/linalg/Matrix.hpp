//
// Created by mtesseract on 6/5/19.
//

#ifndef MACH_MATRIX_HPP
#define MACH_MATRIX_HPP

#include <algorithm>
#include <functional>
#include "math/linalg/Vectors/Vector.hpp"

/*
 * Access is [row][column]
 */

namespace mach {
    template<typename ColVectorBase, typename RowVectorBase, typename T, size_t H, size_t W>
    class Matrix {
        union {
            std::array<T, H * W> m_data;
            std::array<RowVectorBase, H> m_rows;
        };


    public:
        Matrix() : m_data{0} {}

        Matrix(const Matrix &p_m) : m_data(p_m.m_data) {}

        template<typename... Args, typename = typename std::enable_if<sizeof...(Args) == W * H>::type>
        explicit Matrix(Args &&... p_values) : m_data{std::forward<Args>(p_values)...} {}

        RowVectorBase &operator[](size_t p_n) { return m_rows[p_n]; };

        const RowVectorBase &operator[](size_t p_n) const { return m_rows[p_n]; };

        constexpr size_t width() { return W; }

        constexpr size_t height() { return H; }

        constexpr size_t size() { return W * H; }

        template<typename = typename std::enable_if_t<W == H>>
        static constexpr Matrix identity() {
            Matrix output;
            for (size_t row = 0; row < H; ++row) {
                for (size_t col = 0; col < W; ++col) {
                    if (row == col) {
                        output[row][col] = 1.0;
                    } else {
                        output[row][col] = 0.0;
                    }
                }
            }
            return output;
        }

        static constexpr Matrix zero() {
            Matrix output;
            for (size_t row = 0; row < W; ++row) {
                for (size_t col = 0; col < H; ++col) {
                    output[row][col] = 0.0;
                }
            }
            return output;
        }


        friend std::ostream &operator<<(std::ostream &p_os, const Matrix &p_m) {
            for (int i = 0; i < H; ++i) {
                p_os << "[" << p_m[i][0];
                for (int j = 1; j < W; ++j) {
                    p_os << "," << p_m[i][j];
                }
                p_os << "]";
                if (i != H - 1) p_os << std::endl; //So we don't get a trailing whitespace
            }
            return p_os;
        }

        inline RowVectorBase row(size_t p_n) {
            return (*this)[p_n];
        }

        inline ColVectorBase col(size_t p_n) {
            ColVectorBase output;
            for (size_t i = 0; i < H; ++i) {
                output[i] = (*this)[i][p_n];
            }
            return output;
        }

        inline Matrix<RowVectorBase, ColVectorBase, T, W, H> transpose() const {
            Matrix<RowVectorBase, ColVectorBase, T, W, H> output;
            for (size_t row = 0; row < H; ++row) {
                for (size_t col = 0; col < W; ++col) {
                    output[col][row] = (*this)[row][col];
                }
            }
            return output;
        }


        template<typename = typename std::enable_if_t<H == W>>
        inline T determinant() const {
            if (H == 2) return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
            for (size_t c = 0; c < W; ++c) {
                int sign = (int) c % 2 * 2 - 1;
                T ref = sign * (*this)[0][c];
                //Construct a matrix of H-1, W-1, and calculate determinant for those
            }
        }

        template<typename = typename std::enable_if_t<W == H>>
        inline Matrix inverse() const {

        }

        template<typename RColVectorBase, typename RRowVectorBase, typename RT, size_t RH, size_t RW,
                typename = typename std::enable_if_t<W == RH>>
        inline Matrix<ColVectorBase, RRowVectorBase, T, H, RW>
        operator*(const Matrix<RRowVectorBase, RColVectorBase, RT, RH, RW> &p_m) const {
            auto p_m_t = p_m.transpose();
            Matrix<ColVectorBase, RRowVectorBase, T, H, RW> output;
            for (size_t row = 0; row < H; ++row) {
                for (size_t col = 0; col < RW; ++col) {
                    output[row][col] = (*this)[row].dot(p_m_t[col]);
                }
            }
            return output;
        }


        inline RowVectorBase operator*(const RowVectorBase &p_v) const {
            RowVectorBase output;
            for (size_t i = 0; i < output.size(); ++i) {
                output[i] = (*this)[i].dot(p_v);
            }
            return output;
        }



        //Use enable_if to enable determinants only for W == H matrices
        //Use enable_if to enable inverses only for W == H matrices

    };
}

#endif //MACH_MATRIX_HPP
