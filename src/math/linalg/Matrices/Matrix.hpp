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
    template<typename RowVectorBase, typename ColVectorBase, typename T, size_t W, size_t H>
    class Matrix {
        union {
            std::array<T, W * H> m_data;
            std::array<RowVectorBase, H> m_rows;
        };

        static_assert(sizeof(m_rows) != sizeof(m_data));

    public:
        Matrix() : m_data{0} {}

        //Matrix(T p_s) : m_data(p_s) {}

        Matrix(const Matrix &p_m) : m_data(p_m.m_data) {}

        template<typename... Args, typename = typename std::enable_if<sizeof...(Args) == W * H>::type>
        explicit Matrix(Args &&... p_values) : m_data{std::forward<Args>(p_values)...} {}

        virtual RowVectorBase &operator[](size_t p_n) { return m_rows[p_n]; };

        virtual const RowVectorBase &operator[](size_t p_n) const { return m_rows[p_n]; };

        constexpr size_t width() { return W; }

        constexpr size_t height() { return H; }

        constexpr size_t size() { return W * H; }

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

        inline Matrix<ColVectorBase, RowVectorBase, T, H, W> transpose() const {
            Matrix<ColVectorBase, RowVectorBase, T, H, W> output;
            for (size_t row = 0; row < W; ++row) {
                for (size_t col = 0; col < H; ++col) {
                    output[col][row] = (*this)[row][col];
                }
            }
            return output;
        }


        //Use enable_if to enable/disable multiplication between differently sized matrices
        //Use enable_if to enable identity matrices only for W == H matrices
        //Use enable_if to enable determinants only for W == H matrices
        //Use enable_if to enable inverses only for W == H matrices

        template<typename RRowVectorBase, typename RColVectorBase, typename RT, size_t RW, size_t RH,
                typename = typename std::enable_if_t<H == RW>>
        inline Matrix<RRowVectorBase, ColVectorBase, T, W, RH>
        operator*(const Matrix<RRowVectorBase, RColVectorBase, RT, RW, RH> &p_m) const {
            auto p_m_transpose = p_m.transpose();
            Matrix<RRowVectorBase, ColVectorBase, T, W, RH> output;
            for (size_t row = 0; row < output.height(); ++row) {
                for (size_t col = 0; col < output.width(); ++col) {
                    output[row][col] = (*this)[row].dot(p_m_transpose[col]);
                }
            }
            return output;
        }
    };
}

#endif //MACH_MATRIX_HPP
