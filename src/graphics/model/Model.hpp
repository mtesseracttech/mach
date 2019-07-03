//
// Created by mtesseract on 7/3/19.
//

#ifndef MACH_MODEL_HPP
#define MACH_MODEL_HPP

#include <string>

namespace mach::gfx {
	template<typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
	class Model {
		bool load_from_file(const std::string &p_filename) {

		}
	};
}

#endif //MACH_MODEL_HPP
