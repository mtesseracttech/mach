//
// Created by mtesseract on 7/5/19.
//

#ifndef MACH_TRANSFORMCOMPOUND_HPP
#define MACH_TRANSFORMCOMPOUND_HPP

#include <math/linalg/LinAlgTypes.hpp>
#include <math/linalg/Matrix/RotationMatrix.hpp>
#include <math/linalg/Matrix/ScaleMatrix.hpp>
#include <math/linalg/Matrix/MatrixUtils.hpp>
#include <auxiliary/Properties.hpp>
#include <auxiliary/Memory.hpp>

namespace mach {
	enum CoordinateSpace {
		World,
		Local
	};

	namespace core {
		template<typename T>
		class SceneNode;
	}

	template<typename T>
	class TransformCompound {
		Matrix4<T> m_local_transform = Matrix4<T>::identity();

		Vector3<T> m_local_position = Vector3<T>::zero();
		Quaternion<T> m_local_rotation = Quaternion<T>::identity();
		Vector3<T> m_local_scale = Vector3<T>::one();

		Matrix4<T> m_world_transform = Matrix4<T>::identity();

		Vector3<T> m_world_position = Vector3<T>::zero();
		Quaternion<T> m_world_rotation = Quaternion<T>::identity();
		Vector3<T> m_world_scale = Vector3<T>::one();

		bool m_changed = true;

		std::vector<std::weak_ptr<TransformCompound>> m_children;
		std::shared_ptr<TransformCompound> m_parent;

		std::unique_ptr<mach::core::SceneNode<T>> m_scene_node;

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

		void check_mat() {
			if (m_changed) {
				update_transform();
			}
		}

		void mark_changed() {
			m_changed = true;
			notify_children();
		}

		Vector3<T> get_world_matrix_dir(std::size_t m_row) {
			check_mat();
			return Vector3<T>(m_world_transform[m_row]).normalized();
		}

	public:

		TransformCompound(const Vector3<T> &p_position = Vector3<T>::zero(),
		                  const Quaternion<T> &p_rotation = Quaternion<T>::identity(),
		                  const Vector3<T> &p_scale = Vector3<T>::one(),
		                  CoordinateSpace p_space = Local) {
			switch (p_space) {
				case World:
					m_world_position = p_position;
					m_world_rotation = p_rotation;
					m_world_scale = p_scale;
					m_world_transform = math::compose_trs(m_world_position, m_world_rotation, m_world_scale);
					create_local_transform(m_world_transform);
					update_local_vars();
					break;
				case Local:
					m_local_position = p_position;
					m_local_rotation = p_rotation;
					m_local_scale = p_scale;
					m_changed = true;
					break;
			}
		}

		TransformCompound(const TransformCompound &p_transform) = delete;

		TransformCompound &operator=(const TransformCompound &) = delete;

		std::weak_ptr<TransformCompound<T>> &operator[](std::size_t p_n) { return m_children[p_n]; };

		const std::weak_ptr<TransformCompound<T>> &operator[](std::size_t p_n) const { return m_children[p_n]; };

		std::size_t get_child_count() {
			return m_children.size();
		}

		static void add_child(std::shared_ptr<TransformCompound> p_parent, std::weak_ptr<TransformCompound> p_child) {
			auto it = std::find_if(p_parent->m_children.begin(), p_parent->m_children.end(),
			                       [p_child](std::weak_ptr<TransformCompound> p_member_child) {
				                       return equals(p_child, p_member_child);
			                       }
			);
			if (it == p_parent->m_children.end()) {
				p_parent->m_children.push_back(p_child);
				p_child.lock()->m_parent = p_parent;
			}
		}

		PROPERTY(Quaternion<T>, rotation, get_world_rotation, set_world_rotation);
		PROPERTY(Vector3<T>, position, get_world_position, set_world_position);
		PROPERTY_READONLY(Vector3<T>, scale, get_world_scale);
		PROPERTY(Quaternion<T>, local_rotation, get_local_rotation, set_local_rotation);
		PROPERTY(Vector3<T>, local_position, get_local_position, set_local_position);
		PROPERTY(Vector3<T>, local_scale, get_local_scale, set_local_scale);

		Matrix4<T> get_mat() {
			check_mat();
			return m_world_transform;
		}

		void set_world_position(const Vector3<T> &p_position) {
			m_world_position = p_position;
			m_world_transform[3] = Vector4<T>(p_position.x, p_position.y, p_position.z, m_world_transform[3][3]);
			create_local_transform(m_world_transform);
			update_local_vars();
			notify_children();
		}

		void set_world_rotation(const Quaternion<T> &p_rotation) {
			m_world_rotation = p_rotation;
			m_world_transform[3] = Vector4<T>(position.x, position.y, position.z, m_world_transform[3][3]);
			create_local_transform(m_world_transform);
			update_local_vars();
			notify_children();
		}

		Quaternion<T> get_world_rotation() {
			check_mat();
			return m_world_rotation;
		}

		Vector3<T> get_world_position() {
			check_mat();
			return m_world_position;
		}

		Vector3<T> get_world_scale() {
			check_mat();
			return m_world_scale;
		}

		Quaternion<T> get_local_rotation() const {
			return m_local_rotation;
		}

		Vector3<T> get_local_position() const {
			return m_local_position;
		}

		Vector3<T> get_local_scale() const {
			return m_local_scale;
		}

		void set_local_rotation(const Quaternion<T> &p_rotation) {
			mark_changed();
			m_local_rotation = p_rotation;
		}

		void set_local_position(const Vector3<T> &p_position) {
			mark_changed();
			m_local_position = p_position;
		}

		void set_local_scale(const Vector3<T> &p_scale) {
			mark_changed();
			m_local_scale = p_scale;
		}

		PROPERTY_READONLY(Vector3<T>, up, get_up);
		PROPERTY_READONLY(Vector3<T>, down, get_down);
		PROPERTY_READONLY(Vector3<T>, left, get_left);
		PROPERTY_READONLY(Vector3<T>, right, get_right);
		PROPERTY_READONLY(Vector3<T>, forward, get_forward);
		PROPERTY_READONLY(Vector3<T>, backward, get_backward);

		Vector3<T> get_forward() {
			return get_world_matrix_dir(2);
		}

		Vector3<T> get_backward() {
			return -get_world_matrix_dir(2);
		}

		Vector3<T> get_up() {
			return get_world_matrix_dir(1);
		}

		Vector3<T> get_down() {
			return -get_world_matrix_dir(1);
		}

		Vector3<T> get_left() {
			return get_world_matrix_dir(0);
		}

		Vector3<T> get_right() {
			return -get_world_matrix_dir(0);
		}

		PROPERTY_READONLY(bool, changed, get_changed);

		bool get_changed() {
			return m_changed;
		}

	};

	typedef TransformCompound<float> Transform;
	typedef TransformCompound<double> TransformD;
}

#endif //MACH_TRANSFORMCOMPOUND_HPP