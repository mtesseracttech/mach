//
// Created by mtesseract on 7/3/19.
//

#ifndef MACH_VERTEX_HPP
#define MACH_VERTEX_HPP

#include <math/linalg/LinAlgTypes.hpp>

namespace mach::gfx {
	template<typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
	struct Vertex {
		Vector3 <T> m_position;
		Vector3 <T> m_normal;
		Vector3 <T> m_tex_coords;
	};
}

#endif //MACH_VERTEX_HPP
