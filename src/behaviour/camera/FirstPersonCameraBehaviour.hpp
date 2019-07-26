//
// Created by MTesseracT on 2019-07-24.
//

#ifndef MACH_FIRSTPERSONCAMERABEHAVIOUR_HPP
#define MACH_FIRSTPERSONCAMERABEHAVIOUR_HPP


#include <math/linalg/LinAlgTypes.hpp>
#include "core/scene/NodeBehaviour.hpp"
#include <list>

namespace mach::behaviour {
	class FirstPersonCameraBehaviour : public core::NodeBehaviour {
		Vec2 m_mouse_last_pos = MouseInput::position();

		float m_minimum_x = -360;
		float m_maximum_x = 360;
		float m_minimum_y = -60;
		float m_maximum_y = 60;

		float m_camera_movement_speed = 0.0;
		float m_camera_rotation_speed = 0.0;
	private:

		Vec2 m_current_rotation = Vec2::zero();
		Vec2 m_rotations_average = Vec2::zero();
		std::list<Vec2> m_rotations;
		uint32_t m_average_frames = 20;

		Quat m_original_rotation = Quat::identity();
	public:
		FirstPersonCameraBehaviour(float p_movement_speed, float p_rotation_speed):
			m_camera_movement_speed(p_movement_speed),
			m_camera_rotation_speed(p_rotation_speed){
		}

	private:
		void set_owner(std::weak_ptr<core::SceneNode<float>> p_scene_node) override;

		void start() override {}

		void update(float p_delta_time) override;

		void fixed_update() override {}

		void end() override {}


	};
}

#endif //MACH_FIRSTPERSONCAMERABEHAVIOUR_HPP
