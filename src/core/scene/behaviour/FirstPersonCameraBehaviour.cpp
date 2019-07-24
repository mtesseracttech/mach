//
// Created by MTesseracT on 2019-07-24.
//

#include "FirstPersonCameraBehaviour.hpp"
#include "core/scene/SceneNode.hpp"

namespace mach::core {
	void core::FirstPersonCameraBehaviour::update(float p_delta_time) {
		auto mouse_cur_pos = MouseInput::position();
		auto mouse_delta = mouse_cur_pos - m_mouse_last_pos;

		auto camera = m_scene_node.lock();
		if(camera){
			if(MouseInput::pressed(Button1)){
				float camera_rotation_speed = p_delta_time * m_camera_movement_speed;
				Vec2 rotation_deltas = Vec2(mouse_delta.x, mouse_delta.y) * camera_rotation_speed;
				Quat around_x = Quat::from_angle_axis(rotation_deltas.y, camera->transform->right);
				Quat around_y = Quat::from_angle_axis(-rotation_deltas.x, Vec3::up());
				camera->transform->local_rotation *= around_x * around_y;
			}

			float cam_movement_speed = p_delta_time * m_camera_rotation_speed;
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
}