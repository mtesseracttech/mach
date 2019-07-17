//
// Created by mtesseract on 7/5/19.
//

#ifndef MACH_CAMERA_HPP
#define MACH_CAMERA_HPP

#include "math/linalg/TransformCompound.hpp"

namespace mach::gfx {
	template<typename T>
	class Camera {
		TransformCompound<T> m_transform;
		Matrix4<T> m_view;

		bool m_changed = true;

		void check_mat() {
			if (m_changed) {
				update_view();
			}
		}

		void mark_changed() {
			m_changed = true;
		}

		void update_view() {
			//Has to be updated every time m_transform changes.
			m_view = math::view(m_transform.position, m_transform.right, Vector3<T>::up(), m_transform.forward);
		}

		Matrix4<T> get_view_matrix() {
			check_mat();
			return m_view;
		}

	public:
		PROPERTY(const TransformCompound<T>&, transform, get_transform, set_transform);
		PROPERTY_READONLY(Matrix4<T>, view_matrix, get_view);

		const TransformCompound<T> &get_transform() {
			return m_transform;
		}

		void get_transform(const TransformCompound<T> &p_transform) {
			m_transform = p_transform;
		}
	};
}

#endif //MACH_CAMERA_HPP
