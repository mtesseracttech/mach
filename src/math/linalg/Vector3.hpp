//
// Created by mtesseract on 27-5-19.
//

#ifndef MACH_VECTOR3_HPP
#define MACH_VECTOR3_HPP

#include <array>

namespace mach {
	template<typename T>
	class Vector3 {
	public:
		union {
			T x, y, z;
			std::array<T, 3> arr;
		};

	};
}


#endif //MACH_VECTOR3_HPP
