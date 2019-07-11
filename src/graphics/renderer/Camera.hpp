//
// Created by mtesseract on 7/5/19.
//

#ifndef MACH_CAMERA_HPP
#define MACH_CAMERA_HPP

#include "Transform.hpp"

namespace mach::gfx {
	template<typename T>
	class Camera {
		Transform <T> m_transform;
		Matrix4<T> m_view;
	};
}

#endif //MACH_CAMERA_HPP
