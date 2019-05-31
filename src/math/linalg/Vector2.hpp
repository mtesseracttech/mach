//
// Created by mtesseract on 27-5-19.
//

#ifndef MACH_VECTOR2_HPP
#define MACH_VECTOR2_HPP

#include "Vector.hpp"

namespace mach {

	template<typename T>
	class Vector2 : public Vector<T, 2> {
	public:
		union {
			struct {
				T x;
				T y;
			};
			std::array<T, 2> arr;
			T c_arr[2];
		};

		Vector2<T>(T p_x, T p_y) : x(p_x), y(p_y) {}

		Vector2<T>(std::array<T, 2> p_arr) : arr(p_arr) {}

		T &operator[](size_t p_n) override {
			return arr[p_n];
		}

		const T &operator[](size_t p_n) const override {
			return arr[p_n];
		}
	};
}


#endif //MACH_VECTOR2_HPP
