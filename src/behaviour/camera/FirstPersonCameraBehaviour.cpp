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
				Logger::log("Camera rotation and position are not edited in world space, using it like this will likely not work well yet");
			}

			m_rotations_average = Vec2::zero();

			if (MouseInput::pressed(Button1)) {
				m_current_rotation += mouse_delta * m_camera_rotation_speed * 0.02;
				m_current_rotation.x = m_current_rotation.x, math::to_rad(m_minimum_x), math::to_rad(m_maximum_x);
			}


			m_rotations.push_back(m_current_rotation);

			if (m_rotations.size() > m_average_frames) {
				m_rotations.pop_front();
			}

			for (const auto &rotation : m_rotations) {
				m_rotations_average += rotation;
			}

			m_rotations_average /= (float)m_rotations.size();

			m_rotations_average = Vec2(clamp_angle(m_rotations_average.x, math::to_rad(m_minimum_x), math::to_rad(m_maximum_x)),
			                           clamp_angle(m_rotations_average.y, math::to_rad(m_minimum_y), math::to_rad(m_maximum_y)));

			std::cout << m_rotations_average << std::endl;

			Quat around_x = Quat::from_angle_axis(m_rotations_average.y, Vec3::right());
			Quat around_y = Quat::from_angle_axis(-m_rotations_average.x, Vec3::up());
			camera->transform->local_rotation = m_original_rotation * around_x * around_y;

			float cam_movement_speed = p_delta_time * m_camera_movement_speed;
			if (KeyInput::pressed(W)) {
				camera->transform->local_position -= camera->transform->forward * cam_movement_speed;
			}
			if (KeyInput::pressed(S)) {
				camera->transform->local_position -= camera->transform->backward * cam_movement_speed;
			}
			if (KeyInput::pressed(A)) {
				camera->transform->local_position -= camera->transform->left * cam_movement_speed;
			}
			if (KeyInput::pressed(D)) {
				camera->transform->local_position -= camera->transform->right * cam_movement_speed;
			}
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
}