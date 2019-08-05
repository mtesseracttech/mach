//
// Created by MTesseracT on 2019-07-24.
//

#include "FirstPersonCameraBehaviour.hpp"
#include "core/scene/SceneNode.hpp"

namespace mach::behaviour {
	void FirstPersonCameraBehaviour::update(float p_delta_time) {
		Vec2 mouse_cur_pos = MouseInput::position();
		Vec2 mouse_delta = mouse_cur_pos - m_mouse_last_pos;

		auto camera = m_scene_node.lock();
		if (camera) {
			if (camera->transform->has_parent()) {
				Logger::log("Camera rotation and position are not edited in world space, using it like this will likely not work well yet, unless parent's rotation is identity");
			}

			if (MouseInput::pressed(Button1) || m_mode == gfx::Invisible) {
				m_current_rotation += mouse_delta * m_camera_rotation_speed * 0.02;
				m_current_rotation.x = m_current_rotation.x, math::to_rad(m_minimum_x), math::to_rad(m_maximum_x);
			}

			m_rotations.push_back(m_current_rotation);

			if (m_rotations.size() > m_average_frames) {
				m_rotations.pop_front();
			}

			m_rotations_average = Vec2::zero();

			for (const auto &rotation : m_rotations) {
				m_rotations_average += rotation;
			}

			m_rotations_average /= (float)m_rotations.size();

			m_rotations_average = Vec2(clamp_angle(m_rotations_average.x, math::to_rad(m_minimum_x), math::to_rad(m_maximum_x)),
			                           clamp_angle(m_rotations_average.y, math::to_rad(m_minimum_y), math::to_rad(m_maximum_y)));

			Quat around_x = Quat::from_angle_axis(m_rotations_average.y, Vec3::right());
			Quat around_y = Quat::from_angle_axis(-m_rotations_average.x, Vec3::up());
			camera->transform->local_rotation = m_original_rotation * around_x * around_y;

			m_current_velocity = Vec3::zero();

			if (KeyInput::pressed(W)) {
				m_current_velocity += camera->transform->forward;
			}
			if (KeyInput::pressed(S)) {
				m_current_velocity += camera->transform->backward;
			}
			if (KeyInput::pressed(A)) {
				m_current_velocity += camera->transform->left;
			}
			if (KeyInput::pressed(D)) {
				m_current_velocity += camera->transform->right;
			}

			m_current_velocity =  m_current_velocity.normalized() * m_camera_movement_speed;

			m_velocities.push_back(m_current_velocity);

			if (m_velocities.size() > m_average_frames) {
				m_velocities.pop_front();
			}

			m_velocity_average = Vec3::zero();
			for (const auto &velocity : m_velocities) {
				m_velocity_average += velocity;
			}
			m_velocity_average /= (float)m_velocities.size();

			camera->transform->local_position -= m_velocity_average * p_delta_time;
		}
		m_mouse_last_pos = mouse_cur_pos;
	}

	void FirstPersonCameraBehaviour::set_owner(std::weak_ptr<core::SceneNode <float>> p_owner) {
		core::NodeBehaviour::set_owner(p_owner);
		auto camera = p_owner.lock();
		if(camera){
			m_original_rotation = camera->transform->local_rotation;
		}
	}

	void FirstPersonCameraBehaviour::set_cursor_mode(gfx::CursorMode p_mode) {
		m_mode = p_mode;
	}
}