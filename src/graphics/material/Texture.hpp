//
// Created by mtesseract on 7/4/19.
//

#ifndef MACH_TEXTURE_HPP
#define MACH_TEXTURE_HPP

#include <string>

namespace mach::gfx {
	struct Texture {
		uint32_t m_id;
		std::string m_type;
		std::string m_path;
	};
}

#endif //MACH_TEXTURE_HPP
