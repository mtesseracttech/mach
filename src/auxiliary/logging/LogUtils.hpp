//
// Created by mtesseract on 22-6-19.
//

#ifndef MACH_LOGUTILS_HPP
#define MACH_LOGUTILS_HPP

#include <sstream>

namespace mach {
	template<typename T>
	static std::string to_str(const T &p_obj) {
		std::stringstream ss;
		ss << p_obj;
		return ss.str();
	}
}

#endif //MACH_LOGUTILS_HPP
