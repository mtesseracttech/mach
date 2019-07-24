#include <utility>

//
// Created by mtesseract on 7/19/19.
//

#ifndef MACH_NODEBEHAVIOUR_HPP
#define MACH_NODEBEHAVIOUR_HPP

#include <memory>
#include "io/input/KeyInput.hpp"
#include "io/input/MouseInput.hpp"


namespace mach::core {

	template<typename T>
	class SceneNode;

	class NodeBehaviour {
	public:

		std::weak_ptr<SceneNode<float>> m_scene_node = std::weak_ptr<SceneNode<float>>();

		virtual void set_owner(std::weak_ptr<SceneNode<float>> p_scene_node) {
			m_scene_node = p_scene_node;
		}

		virtual void start() = 0;

		virtual void update(float p_delta_time) = 0;

		virtual void fixed_update() = 0;

		virtual void end() = 0;

		virtual ~NodeBehaviour(){
			m_scene_node = std::weak_ptr<SceneNode<float>>();
		}
	};
}


#endif //MACH_NODEBEHAVIOUR_HPP
