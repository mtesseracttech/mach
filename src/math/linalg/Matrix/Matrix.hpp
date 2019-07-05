//
// Created by mtesseract on 6/5/19.
//

#ifndef MACH_MATRIX_HPP
#define MACH_MATRIX_HPP

#include <algorithm>
#include <functional>
#include "math/linalg/Vector.hpp"
#include <memory>

/*
 * Access is [row][column]
 */

namespace mach {
	template<typename T, size_t H, size_t W>
	class Matrix {
		union {
			std::array<T, H * W> m_data;
			std::array<Vector<T, W>, H> m_rows;
		};


	public:
		Matrix() : m_data{0} {}

		Matrix(const T &p_s) { m_data.fill(p_s); }

		Matrix(const Matrix &p_m) : m_data(p_m.m_data) {}

		template<typename... Args, typename = typename std::enable_if<sizeof...(Args) == W * H>::type>
		explicit Matrix(Args &&... p_values) : m_data{static_cast<T>(std::forward<Args>(p_values))...} {}

		Vector<T, W> &operator[](size_t p_n) { return m_rows[p_n]; };

		const Vector<T, W> &operator[](size_t p_n) const { return m_rows[p_n]; };

		constexpr size_t width() { return W; }

		constexpr size_t height() { return H; }

		constexpr size_t size() { return W * H; }

		inline const T *get_value_ptr() const {
			return m_data.data();
		}

		//template<typename = typename std::enable_if_t<W == H>>
		static constexpr Matrix identity() {
			static_assert(W == H, "Identity matrices only exist can only be created for square matrices");
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
			return Matrix(0.0);
		}


		friend std::ostream &operator<<(std::ostream &p_os, const Matrix &p_m) {
			for (int i = 0; i < H; ++i) {
				p_os << std::fixed << std::setprecision(3) << "[" << p_m[i][0];
				for (int j = 1; j < W; ++j) {
					p_os << "," << p_m[i][j];
				}
				p_os << "]";
				if (i != H - 1) p_os << std::endl; //So we don't get a trailing whitespace
			}
			return p_os;
		}

		inline Vector<T, W> row(size_t p_n) {
			return (*this)[p_n];
		}

		inline Vector<T, H> col(size_t p_n) {
			Vector<T, H> output;
			for (size_t i = 0; i < H; ++i) {
				output[i] = (*this)[i][p_n];
			}
			return output;
		}

		inline Matrix<T, W, H> transpose() const {
			Matrix<T, W, H> output;
			for (size_t row = 0; row < H; ++row) {
				for (size_t col = 0; col < W; ++col) {
					output[col][row] = (*this)[row][col];
				}
			}
			return output;
		}

		inline T determinant() const {
			static_assert(W == H, "Determinants can only be created from square matrices");
			if constexpr (W == 2) {
				return (m_data[0] * m_data[3]) - (m_data[1] * m_data[2]);
			} else {
				//Creating the return value
				T result = T();
				//Preparing the information for the new matrix
				constexpr size_t lower_w = (W - 1);
				constexpr size_t lower_h = (H - 1);
				for (int i = 0; i < W; ++i) {
					//Going though the top row
					const T lh = m_rows[0][i];
					//Constructing smaller matrix
					Matrix<T, lower_w, lower_h> rh;
					//The column at which we are inserting the cofactors
					int rhw = 0;
					for (int w = 0; w < W; ++w) {
						//If the current column is equal to the reference cell's column, we skip it
						if (w == i) {
							continue;
						}
						//Filling in the new matrix' column
						for (int h = 1; h < H; ++h) {
							rh[rhw][h - 1] = m_rows[h][w];
						}
						++rhw;
					}
					//Doing the + - + pattern
					if ((i & 1) == 0) {
						result += lh * rh.determinant();
					} else {
						result -= lh * rh.determinant();
					}
				}
				return result;
			}
		}

		inline Matrix adjugate() const {
			static_assert(W == H, "Adugates can only be created from square matrices");
			Matrix result;
			if constexpr (W == 2) { //Directly implemented because the downscale algorithm does not work on Mat2
				result[0][0] = m_rows[1][1];
				result[0][1] = -m_rows[0][1];
				result[1][0] = -m_rows[1][0];
				result[1][1] = m_rows[0][0];
			} else {
				//Preparing the information for the cofactor matrices
				constexpr size_t lower_w = (W - 1);
				constexpr size_t lower_h = (H - 1);
				for (size_t r = 0; r < H; ++r) {
					for (size_t c = 0; c < W; ++c) {
						//Constructing smaller cofactor matrix to get determinant for cofactors
						Matrix<T, lower_w, lower_h> small_cof_mat;

						//Filling in smaller matrix
						size_t small_idx_row = 0; //"real" index of the row in the cofactor matrix
						for (size_t cofactor_row = 0; cofactor_row < H; ++cofactor_row) {
							size_t small_idx_col = 0; //"real" index of the column in the cofactor matrix
							if (cofactor_row == r) {
								continue;
							}
							for (size_t cofactor_col = 0; cofactor_col < W; ++cofactor_col) {
								if (cofactor_col == c) {
									continue;
								} else {
									small_cof_mat[small_idx_row][small_idx_col] = m_rows[cofactor_row][cofactor_col];
								}
								++small_idx_col;
							}
							++small_idx_row;
						}
						//Constructing cofactor matrix
						if (((r + c) & 1) == 0) {
							result[c][r] = (small_cof_mat.determinant());
						} else {
							result[c][r] = -(small_cof_mat.determinant());
						}
					}
				}
				result.transpose();
			}
			return result;
		}

		inline Matrix inverse() const {
			static_assert(W == H, "Inverses can only be created from square matrices");
			T det = determinant();
			if (det != 0.0) {
				return adjugate() * (1.0 / det);
			} else {
				return identity();
			}
		}


		template<typename RT, size_t RH, size_t RW>
		inline Matrix<T, H, RW> operator*(const Matrix<RT, RH, RW> &p_m) const {
			static_assert(W == RH, "Matrix multiplication is only defined for matrices with matching inner dimensions");
			auto p_m_t = p_m.transpose();
			Matrix<T, H, RW> output;
			for (size_t row = 0; row < H; ++row) {
				for (size_t col = 0; col < RW; ++col) {
					output[row][col] = (*this)[row].dot(p_m_t[col]);
				}
			}
			return output;
		}


		inline Vector<T, W> operator*(const Vector<T, W> &p_v) const {
			Vector<T, W> output;
			for (size_t i = 0; i < output.size(); ++i) {
				output[i] = (*this)[i].dot(p_v);
			}
			return output;
		}

		inline Matrix operator*(const T &p_s) const {
			Matrix output;
			for (size_t r = 0; r < H; ++r) {
				output[r] = m_rows[r] * p_s;
			}
			return output;
		}

		inline Matrix operator/(const T &p_s) const {
			return (*this) * (1.0 / p_s);
		}

		friend inline Matrix operator*(T &p_s, const Matrix &rhs) {
			return rhs * p_s;
		}


		inline bool operator==(const Matrix &p_m) const {
			for (size_t i = 0; i < H; ++i) {
				if (!(m_rows[i] == p_m.m_rows[i])) {
					return false;
				}
			}
			return true;
		}
	};
}

#endif //MACH_MATRIX_HPP
