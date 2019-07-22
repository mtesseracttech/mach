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
		Camera(const std::shared_ptr<TransformCompound<T>> p_transform = std::make_shared<TransformCompound<T>>(),
		       const std::weak_ptr<SceneHierarchy> &p_scene = std::weak_ptr<SceneHierarchy>(),
		       const std::string &p_name = "Camera") : SceneNode<T>(p_transform, p_scene, p_name) {
		}

		PROPERTY_READONLY(Matrix4<T>, view_matrix, get_view);

		Matrix4<T> get_view() {
			return math::view(this->m_transform.position,
			                  this->m_transform.right,
			                  Vector3<T>::up(),
			                  this->m_transform.forward);
		}
	};
}

#endif //MACH_CAMERA_HPP
