//
// Created by mtesseract on 7/5/19.
//

#ifndef MACH_CAMERA_HPP
#define MACH_CAMERA_HPP

#include "SceneNode.hpp"

namespace mach::core {
	template<typename T>
	class Camera : public SceneNode<T> {
	public:
		explicit Camera(std::weak_ptr<SceneHierarchy<T>> p_scene = std::weak_ptr<SceneHierarchy<T>>(),
		                const std::string &p_name = "Camera") : SceneNode<T>(p_scene, p_name) {
		}

		PROPERTY_READONLY(Matrix4<T>, view_matrix, get_view);

		Matrix4<T> get_view() {
			Vector3<T> right = this->m_transform->forward.cross(Vector3<T>::up()).normalized();
			Vector3<T> up = right.cross(this->m_transform->forward).normalized();
			Vector3<T> forward = this->m_transform->forward;

			return math::view(this->m_transform->position, right, up, forward);
		}
	};
}

#endif //MACH_CAMERA_HPP
