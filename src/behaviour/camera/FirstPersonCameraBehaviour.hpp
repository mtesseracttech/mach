//
// Created by MTesseracT on 2019-07-24.
//

#ifndef MACH_FIRSTPERSONCAMERABEHAVIOUR_HPP
#define MACH_FIRSTPERSONCAMERABEHAVIOUR_HPP


#include <math/linalg/LinAlgTypes.hpp>
#include "core/scene/NodeBehaviour.hpp"

namespace mach::behaviour {
	class FirstPersonCameraBehaviour : public core::NodeBehaviour {
		Vec2 m_mouse_last_pos = MouseInput::position();

		float m_camera_movement_speed = 0;
		float m_camera_rotation_speed = 0;
	public:
		FirstPersonCameraBehaviour(float p_movement_speed, float p_rotation_speed):
			m_camera_movement_speed(p_movement_speed),
			m_camera_rotation_speed(p_rotation_speed) {
		}

	private:
		void start() override {}

		void update(float p_delta_time) override;

		void fixed_update() override {}

		void end() override {

		}
	};
}

#endif //MACH_FIRSTPERSONCAMERABEHAVIOUR_HPP
