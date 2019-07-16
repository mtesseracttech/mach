//
// Created by mtesseract on 7/5/19.
//

#ifndef MACH_CAMERA_HPP
#define MACH_CAMERA_HPP

#include "math/linalg/TransformCompound.hpp"

namespace mach::gfx {
	template<typename T>
	class Camera {
		TransformCompound <T> m_transform;
		Matrix4<T> m_view;
	};
}

#endif //MACH_CAMERA_HPP
