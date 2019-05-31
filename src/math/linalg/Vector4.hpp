//
// Created by mtesseract on 27-5-19.
//

#ifndef MACH_VECTOR4_HPP
#define MACH_VECTOR4_HPP

#include <array>

namespace mach {
	template<typename T>
	class Vector4 {
	public:
		union {
			T x, y, z, w;
			std::array<T, 4> arr;
		};
	};
}


#endif //MACH_VECTOR4_HPP
