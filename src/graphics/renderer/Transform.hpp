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
				try {
					auto child = m_children[i].lock();
					child->mark_changed();
				}

				catch (std::bad_weak_ptr &ptr) {
					Logger::log("Null Child Found", Error);
				}
			}
		}

		void update_transform() {
			m_local_transform = math::translate(m_local_position) *
			                    RotationMatrix<T>::from_quat(m_local_rotation).to_mat4() *
			                    ScaleMatrix<T>::scale_along_cardinal_axes(m_local_scale).to_mat4();
			if (m_parent) {
				m_world_transform = m_parent->get_mat() * m_local_transform;
				Logger::log("Yes parent");
			} else {
				m_world_transform = m_local_transform;
				Logger::log("No parent");
			}
			math::decompose_trs(m_world_transform, &m_world_position, &m_world_rotation, &m_world_scale);
			notify_children();
			m_changed = false;
		}

		explicit Transform(std::shared_ptr<Transform> p_parent,
		                   const Vector3<T> &p_position,
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
				m_parent(p_parent) {
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

		void add_child(const std::weak_ptr<Transform> p_child) {
			m_children.push_back(p_child);
		}

	public:
		static std::shared_ptr<Transform> create(const Vector3<T> &p_position,
		                                         const Quaternion<T> &p_rotation = Quaternion<T>::identity(),
		                                         const Vector3<T> &p_scale = Vector3<T>::one(),
		                                         std::shared_ptr<Transform> p_parent = nullptr) {
			auto new_transform = std::make_shared<Transform>(Transform(p_parent, p_position, p_rotation, p_scale));
			if (p_parent) {
				p_parent->add_child(new_transform);
			}
			return new_transform;
		}

		PROPERTY_READONLY(Quaternion<T>, rotation, get_world_rotation);
		PROPERTY_READONLY(Vector3<T>, position, get_world_position);
		PROPERTY_READONLY(Vector3<T>, scale, get_world_scale);
		PROPERTY(Quaternion<T>, local_rotation, get_local_rotation, set_local_rotation);
		PROPERTY(Vector3<T>, local_position, get_local_position, set_local_position);
		PROPERTY(Vector3<T>, local_scale, get_local_scale, set_local_scale);

		Matrix4<T> get_mat() {
			check_mat();
			return m_local_transform;
		}

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
