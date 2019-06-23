//
// Created by mtesseract on 6/17/19.
//

#ifndef MACH_MATHUTILS_HPP
#define MACH_MATHUTILS_HPP

namespace mach {
	template<typename T>
	class MathUtils {
	public:
		static constexpr T pi = 3.14159265358979323846;
		static constexpr T e = 2.71828182845904523536;

		static inline T lerp(T p_start, T p_end, T p_t) {
			return p_start + (p_end - p_start) * p_t;
		}

		static inline T to_rad(T p_deg) {
			const T rad = pi / 180.0;
			return p_deg * rad;
		}

		static inline T to_deg(T p_rad) {
			const T deg = 180.0 / pi;
			return p_rad * deg;
		}
	};
}

#endif //MACH_MATHUTILS_HPP
