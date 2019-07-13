//
// Created by mtesseract on 7/5/19.
//

#ifndef MACH_TRANSFORM_HPP
#define MACH_TRANSFORM_HPP

#include <math/linalg/LinAlgTypes.hpp>
#include <math/linalg/Matrix/RotationMatrix.hpp>
#include <math/linalg/Matrix/ScaleMatrix.hpp>
#include <math/linalg/Matrix/MatrixUtils.hpp>
#include <auxiliary/Properties.hpp>


namespace mach {
	template<typename T>
	class Transform {
		Matrix4<T> m_local_transform;

		Vector3<T> m_local_position;
		Quaternion<T> m_local_rotation;
		Vector3<T> m_local_scale;

		Matrix4<T> m_world_transform;

		Vector3<T> m_world_position;
		Quaternion<T> m_world_rotation;
		Vector3<T> m_world_scale;

		bool m_changed;

		std::vector<std::weak_ptr<Transform>> m_children;
		std::shared_ptr<Transform> m_parent;

		void notify_children() {
			for (int i = m_children.size() - 1; i >= 0; --i) {
				auto child = m_children[i].lock();
				child->mark_changed();
			}
		}

		void update_transform() {
			m_local_transform = math::compose_trs(m_local_position, m_local_rotation, m_local_scale);
			if (m_parent) {
				m_world_transform = m_parent->get_mat() * m_local_transform;
			} else {
				m_world_transform = m_local_transform;
			}
			update_world_vars();
			notify_children();
			m_changed = false;
		}

		//To be used in conjunction with the world pos/rot/scale setters
		Matrix4<T> create_local_transform(const Matrix4<T> &p_world_transform) {
			if (m_parent) {
				return m_local_transform = m_parent->get_mat().inverse() * p_world_transform;
			} else {
				return m_local_transform = p_world_transform;
			}
		}

		void update_world_vars() {
			math::decompose_trs(m_world_transform, &m_world_position, &m_world_rotation, &m_world_scale);
		}

		void update_local_vars() {
			math::decompose_trs(m_local_transform, &m_local_position, &m_local_rotation, &m_local_scale);
		}

		void add_child(std::weak_ptr<Transform> p_child) {
			auto it = std::find(m_children.begin(), m_children.end(),
			                    p_child); //This line will not work for some reason
			if (it == m_children.end()) {
				m_children.push_back(p_child);
				p_child.lock()->m_parent = this; //This line will not work
			}
		}

		void check_mat() {
			if (m_changed) {
				update_transform();
			}
		}

		void mark_changed() {
			m_changed = true;
			notify_children();
		}

	public:

		Transform(const Vector3<T> &p_position = Vector3<T>::zero(),
		          const Quaternion<T> &p_rotation = Quaternion<T>::identity(),
		          const Vector3<T> &p_scale = Vector3<T>::one()) :
				m_local_position(p_position),
				m_local_rotation(p_rotation),
				m_local_scale(p_scale),
				m_local_transform(Matrix4<T>::identity()),
				m_world_position(Vector3<T>::zero()),
				m_world_rotation(Quaternion<T>::identity()),
				m_world_scale(Vector3<T>::one()),
				m_world_transform(Matrix4<T>::identity()),
				m_changed(true),
				m_parent(nullptr) {
		}

		static void add_child(std::shared_ptr<Transform> p_parent, std::weak_ptr<Transform> p_child) {
			if (p_parent && !p_child.expired()) {
				p_parent->m_children.push_back(p_child);
				p_child.lock()->m_parent = p_parent;
			}
		}

		PROPERTY_READONLY(Quaternion<T>, rotation, get_world_rotation);
		PROPERTY(Vector3<T>, position, get_world_position, set_world_position);
		PROPERTY_READONLY(Vector3<T>, scale, get_world_scale);
		PROPERTY(Quaternion<T>, local_rotation, get_local_rotation, set_local_rotation);
		PROPERTY(Vector3<T>, local_position, get_local_position, set_local_position);
		PROPERTY(Vector3<T>, local_scale, get_local_scale, set_local_scale);

		Matrix4<T> get_mat() {
			check_mat();
			return m_local_transform;
		}

		void set_world_position(const Vector3<T> &p_position) {
			m_world_position = p_position;
			m_world_transform[3] = Vector4<T>(p_position.x, p_position.y, p_position.z, m_world_transform[3][3]);
			create_local_transform(m_world_transform);
			update_local_vars();
			notify_children();
		};

		void set_world_position(const Quaternion<T> &p_rotation) {
			m_world_rotation = p_rotation;
			//m_world_transform[3] = Vector4<T>(p_position.x, p_position.y, p_position.z, m_world_transform[3][3]);
			create_local_transform(m_world_transform);
			update_local_vars();
			notify_children();
		};

		Quaternion<T> get_world_rotation() {
			check_mat();
			return m_world_rotation;
		};

		Vector3<T> get_world_position() {
			check_mat();
			return m_world_position;
		};

		Vector3<T> get_world_scale() {
			check_mat();
			return m_world_scale;
		};

		Quaternion<T> get_local_rotation() const {
			return m_local_rotation;
		};

		Vector3<T> get_local_position() const {
			return m_local_position;
		};

		Vector3<T> get_local_scale() const {
			return m_local_scale;
		};

		void set_local_rotation(const Quaternion<T> &p_rotation) {
			mark_changed();
			m_local_rotation = p_rotation;
		};

		void set_local_position(const Vector3<T> &p_position) {
			mark_changed();
			m_local_position = p_position;
		};

		void set_local_scale(const Vector3<T> &p_scale) {
			mark_changed();
			m_local_scale = p_scale;
		};
	};
}

#endif //MACH_TRANSFORM_HPP
