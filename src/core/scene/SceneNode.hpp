//
// Created by mtesseract on 7/19/19.
//

#ifndef MACH_SCENENODE_HPP
#define MACH_SCENENODE_HPP

#include "math/linalg/TransformCompound.hpp"
#include "NodeBehaviour.hpp"
#include <memory>
#include <vector>

namespace mach::core {

	template<typename T>
	class SceneHierarchy;

	template<typename T>
	class SceneNode : public std::enable_shared_from_this<SceneNode<T>> {
	protected:
		std::shared_ptr<TransformCompound<T>> m_transform;
		std::vector<std::shared_ptr<NodeBehaviour>> m_behaviours;
		std::weak_ptr<SceneHierarchy<T>> m_scene;
		std::string m_name;

	public:
		explicit SceneNode(std::weak_ptr<SceneHierarchy<T>> p_scene,
		                   const std::string &p_name = "N/A") :
				m_transform(std::make_shared<TransformCompound<T>>(TransformCompound<T>())),
				m_name(p_name),
				m_scene(p_scene) {
		}

		explicit SceneNode(std::weak_ptr<SceneNode> p_parent,
		                   const std::string &p_name = "N/A") :
				m_transform(std::make_shared<TransformCompound<T>>(TransformCompound<T>())),
				m_name(p_name),
				m_scene(p_parent.lock()->scene()) {
		}

		static std::shared_ptr<SceneNode> create(std::weak_ptr<SceneHierarchy<T>> p_scene,
		                                         const std::string &p_name = "N/A") {
			std::shared_ptr<SceneNode> node = std::make_shared<SceneNode>(p_scene, p_name);
			node->m_transform->user(node->weak_from_this());
			node->m_scene.lock()->add_node(node);
			return node;
		}

		static std::shared_ptr<SceneNode> create(std::weak_ptr<SceneNode> p_parent,
		                                         const std::string &p_name = "N/A") {
			std::shared_ptr<SceneNode> node = std::make_shared<SceneNode>(p_parent, p_name);
			node->m_transform->user(node->weak_from_this());
			p_parent.lock()->transform()->add_child(node->m_transform);
			return node;
		}

		~SceneNode() {
			Logger::log(m_name + " getting destroyed", Debug);
		}

		void add_behaviour(std::shared_ptr<NodeBehaviour> p_behaviour) {
			p_behaviour->set_owner(this->weak_from_this());
			m_behaviours.push_back(p_behaviour);
		}

//		PROPERTY(const std::weak_ptr<SceneHierarchy<T>> &, scene, get_scene, set_scene);

		const std::weak_ptr<SceneHierarchy<T>> &scene() {
			return m_scene;
		}

		void scene(const std::weak_ptr<SceneHierarchy<T>> &p_scene) {
			m_scene = p_scene;
		}

//		PROPERTY(const std::shared_ptr<TransformCompound<T>>, transform, get_transform, set_transform);

		const std::shared_ptr<TransformCompound<T>> transform() const {
			return m_transform;
		}


//		PROPERTY(const std::string &, name, get_name, set_name);

		const std::string &name() {
			return m_name;
		}

		void name(const std::string &p_name) {
			m_name = p_name;
		}

		void update(float p_delta_time) {
			for (int i = m_behaviours.size() - 1; i >= 0; --i) {
				m_behaviours[i]->update(p_delta_time);
			}
			for (int i = m_transform->get_child_count() - 1; i >= 0; --i) {
				std::shared_ptr<TransformCompound<T>> child_transform = (*m_transform)[i];
				if (child_transform) {
					auto child = child_transform->user().lock();
					if (child) {
						child->update(p_delta_time);
					}
				}
			}
		}
	};
}


#endif //MACH_SCENENODE_HPP
