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
	class TransformCompound : public std::enable_shared_from_this<TransformCompound<T>> {
		Matrix4<T> m_local_transform = Matrix4<T>::identity();

		Vector3<T> m_local_position = Vector3<T>::zero();
		Quaternion<T> m_local_rotation = Quaternion<T>::identity();
		Vector3<T> m_local_scale = Vector3<T>::one();

		Matrix4<T> m_world_transform = Matrix4<T>::identity();

		Vector3<T> m_world_position = Vector3<T>::zero();
		Quaternion<T> m_world_rotation = Quaternion<T>::identity();
		Vector3<T> m_world_scale = Vector3<T>::one();

		bool m_changed = true;

		std::vector<std::shared_ptr<TransformCompound>> m_children;
		std::weak_ptr<TransformCompound> m_parent;

		std::weak_ptr<core::SceneNode<T>> m_user = std::weak_ptr<core::SceneNode<T>>();

		void notify_children() {
			for (int i = m_children.size() - 1; i >= 0; --i) {
				m_children[i]->mark_changed();
			}
		}

		void update_transform() {
			m_local_transform = math::compose_trs(m_local_position, m_local_rotation, m_local_scale);
			auto parent = m_parent.lock();
			if (parent) {
				m_world_transform = m_local_transform *  parent->get_mat();
			} else {
				m_world_transform = m_local_transform;
			}
			update_world_vars();
			notify_children();
			m_changed = false;
		}

		//To be used in conjunction with the world pos/rot/scale setters
		void create_local_transform(const Matrix4<T> &p_world_transform) {
			mark_changed();
			auto parent = m_parent.lock();
			if (parent) {
				m_local_transform = p_world_transform * parent->get_mat().inverse() ;
			} else {
				m_local_transform = p_world_transform;
			}
			m_world_transform = p_world_transform;
			update_local_vars();
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

		Vector3<T> get_world_dir(std::size_t m_row) {
			check_mat();
			return Vector3<T>(m_world_transform[m_row]).normalized();
		}

		Vector3<T> get_world_dir_from_quat(Vector3<T> p_dir){
			check_mat();
			return (p_dir * m_world_rotation).normalized();
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

		TransformCompound &operator=(const TransformCompound &) = delete;

		std::shared_ptr<TransformCompound<T>> &operator[](std::size_t p_n) { return m_children[p_n]; };

		const std::shared_ptr<TransformCompound<T>> &operator[](std::size_t p_n) const { return m_children[p_n]; };

		std::size_t get_child_count() const {
			return m_children.size();
		}

		std::size_t get_children_count_deep() const {
			std::size_t total = get_child_count();
			for (const auto &child : m_children) {
				total += child->get_children_count_deep();
			}
			return total;
		}

		void add_child(std::shared_ptr<TransformCompound> p_child) {
			if (p_child) {
				auto it = std::find(m_children.begin(), m_children.end(), p_child);
				if (it == m_children.end()) {
					m_children.push_back(p_child);
					p_child->m_parent = this->weak_from_this();
				}
			}
		}

//		PROPERTY(Quaternion<T>, rotation, get_world_rotation, set_world_rotation);
//		PROPERTY(Vector3<T>, position, get_world_position, set_world_position);
//		PROPERTY(Vector3<T>, scale, get_world_scale, set_world_scale);
		PROPERTY_READONLY(Quaternion<T>, rotation, get_world_rotation);
		PROPERTY_READONLY(Vector3<T>, position, get_world_position);
		PROPERTY_READONLY(Vector3<T>, scale, get_world_scale);
		PROPERTY(Quaternion<T>, local_rotation, get_local_rotation, set_local_rotation);
		PROPERTY(Vector3<T>, local_position, get_local_position, set_local_position);
		PROPERTY(Vector3<T>, local_scale, get_local_scale, set_local_scale);

		Matrix4<T> get_mat() {
			check_mat();
			return m_world_transform;
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


//		void set_world_position(const Vector3<T> &p_position) {
//			create_local_transform(math::compose_trs(p_position, m_world_rotation, m_world_scale));
//		}
//
//		void set_world_rotation(const Quaternion<T> &p_rotation){
//			create_local_transform(math::compose_trs(m_world_position, p_rotation, m_world_scale));
//		}
//
//		void set_world_scale(const Vector3<T> &p_scale) {
//			create_local_transform(math::compose_trs(m_world_position, m_world_rotation, p_scale));
//		}

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
			return get_world_dir(2);
		}

		Vector3<T> get_backward() {
			return -get_world_dir(2);
		}

		Vector3<T> get_up() {
			return get_world_dir(1);
		}

		Vector3<T> get_down() {
			return -get_world_dir(1);
		}

		Vector3<T> get_right() {
			return get_world_dir(0);
		}

		Vector3<T> get_left() {
			return -get_world_dir(0);
		}

		PROPERTY_READONLY(bool, changed, get_changed);

		bool get_changed() {
			return m_changed;
		}

		PROPERTY(std::weak_ptr<core::SceneNode<T>>, user, get_user, set_user);

		std::weak_ptr<core::SceneNode<T>> get_user() {
			return m_user;
		}

		void set_user(std::weak_ptr<core::SceneNode<T>> p_user) {
			m_user = p_user;
		}

		PROPERTY(std::weak_ptr<TransformCompound>, parent, get_parent, set_parent);

		std::weak_ptr<TransformCompound> get_parent() {
			return m_parent;
		}

		void set_parent(std::weak_ptr<TransformCompound> p_parent) {
			m_parent = p_parent;
		}

		bool has_parent(){
			return m_parent.lock();
		}
	};

	typedef TransformCompound<float> Transform;
	typedef TransformCompound<double> TransformD;
}

#endif //MACH_TRANSFORMCOMPOUND_HPP
