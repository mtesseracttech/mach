//
// Created by mtesseract on 6/17/19.
//

#ifndef MACH_MATHUTILS_HPP
#define MACH_MATHUTILS_HPP

#include <math/linalg/LinAlgTypes.hpp>

namespace mach::math {
	constexpr double e = 2.71828182845904523536;
	constexpr double pi = 3.14159265358979323846;
	constexpr double deg_to_rad = pi / 180.0;
	constexpr double rad_to_deg = 180.0 / pi;

	template<typename T>
	inline T lerp(T p_start, T p_end, T p_t) {
		return p_start + (p_end - p_start) * p_t;
	}

	template<typename T>
	inline T to_rad(T p_deg) {
		return p_deg * deg_to_rad;
	}

	template<typename T>
	inline T to_deg(T p_rad) {
		return p_rad * rad_to_deg;
	}

	template <typename T>
	inline int sign(const T &p_val) {
		return (T(0) < p_val) - (p_val < T(0));
	}

	template<typename T>
	inline Vector<T, 3> color_over_time(T p_a){
		T t = std::fmod(p_a, 1.0) * 2 * pi;
		auto colors_non_normalized = Vector<T,3>(std::max<T>(std::sin(t), 0.0), std::max<T>(std::sin(t + pi / 3.0),0.0), std::max<T>(std::sin(t + 2 * pi / 3.0),0.0));
		return colors_non_normalized / 2.0;
	}
}

#endif //MACH_MATHUTILS_HPP
