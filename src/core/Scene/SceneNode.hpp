//
// Created by mtesseract on 7/19/19.
//

#ifndef MACH_SCENENODE_HPP
#define MACH_SCENENODE_HPP

#include "math/linalg/TransformCompound.hpp"
#include "Behaviour/SceneBehaviour.hpp"

namespace mach::core {
	template<typename T>
	class SceneNode {
	protected:
		TransformCompound<T> m_transform;
		std::vector<SceneBehaviour> m_behaviours;
	public:
		PROPERTY(const TransformCompound<T>&, transform, get_transform, set_transform);

		const TransformCompound<T> &get_transform() {
			return m_transform;
		}

		void set_transform(const TransformCompound<T> &p_transform) {
			m_transform = p_transform;
		}

		void update() {

		}
	};
}


#endif //MACH_SCENENODE_HPP
