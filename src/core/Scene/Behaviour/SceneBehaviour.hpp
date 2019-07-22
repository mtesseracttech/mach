//
// Created by mtesseract on 7/19/19.
//

#ifndef MACH_SCENEBEHAVIOUR_HPP
#define MACH_SCENEBEHAVIOUR_HPP

namespace mach::core {
	class SceneBehaviour {
		std::weak_ptr<SceneNode < float>> m_parent;

	public:
		virtual void start() = 0;

		virtual void update() = 0;

		virtual void fixed_update() = 0;

		virtual void destroy() = 0;


		virtual ~SceneBehaviour() = default;;
	};
}


#endif //MACH_SCENEBEHAVIOUR_HPP
