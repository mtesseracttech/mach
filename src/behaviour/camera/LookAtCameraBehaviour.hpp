//
// Created by MTesseracT on 2019-07-24.
//

#ifndef MACH_LOOKATCAMERABEHAVIOUR_HPP
#define MACH_LOOKATCAMERABEHAVIOUR_HPP


#include <core/scene/NodeBehaviour.hpp>

namespace mach::behaviour{
	class LookAtCameraBehaviour : public core::NodeBehaviour {
	public:
		void start() override;

		void update(float p_delta_time) override;

		void fixed_update() override;

		void end() override;
	};
}


#endif //MACH_LOOKATCAMERABEHAVIOUR_HPP
