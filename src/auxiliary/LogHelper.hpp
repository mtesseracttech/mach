//
// Created by mtesseract on 27-5-19.
//

#ifndef MACH_LOGHELPER_HPP
#define MACH_LOGHELPER_HPP


#include <ostream>
#include <math/linalg/Vector2.hpp>

namespace mach {
	namespace LogHelper {
		template<typename T>
		std::ostream &operator<<(std::ostream &p_os, const Vector2<T> &p_v) {
			return p_os << p_v.to_str();
		}

	};
}


#endif //MACH_LOGHELPER_HPP
