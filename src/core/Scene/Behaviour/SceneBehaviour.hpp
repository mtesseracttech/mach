//
// Created by mtesseract on 7/19/19.
//

#ifndef MACH_SCENEBEHAVIOUR_HPP
#define MACH_SCENEBEHAVIOUR_HPP

namespace mach::core {
	class SceneBehaviour {
		std::shared_ptr <SceneNode> m_parent;

		void start() = 0;

		void update() = 0;

		void fixed_update() = 0;

		void destroy() = 0;
	};
}


#endif //MACH_SCENEBEHAVIOUR_HPP
