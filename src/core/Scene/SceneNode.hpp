//
// Created by mtesseract on 7/19/19.
//

#ifndef MACH_SCENENODE_HPP
#define MACH_SCENENODE_HPP

#include "math/linalg/TransformCompound.hpp"
#include "Behaviour/SceneBehaviour.hpp"
#include <memory>

namespace mach::core {

	class SceneHierarchy;

	template<typename T>
	class SceneNode {
	protected:
		std::shared_ptr<TransformCompound<T>> m_transform;
		std::vector<SceneBehaviour> m_behaviours;
		std::weak_ptr<SceneHierarchy> m_scene;
		std::string m_name;

	public:
		SceneNode(const std::shared_ptr<TransformCompound<T>> &p_transform,
		          const std::weak_ptr<SceneHierarchy> &p_scene,
		          const std::string &p_name = "N/A") : m_transform(p_transform),
		                                               m_name(p_name),
		                                               m_scene(p_scene) {
			p_transform->user = this;
		}

		void add_behaviour(const SceneBehaviour &p_behaviour) {
			m_behaviours.push_back(p_behaviour);
		}

		PROPERTY(const std::weak_ptr<SceneHierarchy> &, scene, get_scene, set_scene);

		const std::weak_ptr<SceneHierarchy> &get_scene() {
			return m_scene;
		}

		void set_scene(const std::weak_ptr<SceneHierarchy> &p_scene) {
			m_scene = p_scene;
		}

		PROPERTY(std::shared_ptr<TransformCompound<T>>, transform, get_transform, set_transform);

		std::shared_ptr<TransformCompound<T>> get_transform() {
			return m_transform;
		}

		void set_transform(std::shared_ptr<TransformCompound<T>> p_transform) {
			m_transform = p_transform;
		}

		PROPERTY(const std::string &, name, get_name, set_name);

		const std::string &get_name() {
			return m_name;
		}

		void set_name(const std::string &p_name) {
			m_name = p_name;
		}

		void update() {
			for (int i = m_behaviours.size() - 1; i >= 0; --i) {
				m_behaviours[i].update();
			}
			for (int i = m_transform->get_child_count() - 1; i >= 0; --i) {
				std::shared_ptr<TransformCompound<T>> child_transform = (*m_transform)[i];
				if (child_transform) {
					if (child_transform->user) {
						child_transform->user->update();
					}
				}
			}
		}
	};
}


#endif //MACH_SCENENODE_HPP
