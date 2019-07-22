//
// Created by mtesseract on 7/21/19.
//

#ifndef MACH_SCENEHIERARCHY_HPP
#define MACH_SCENEHIERARCHY_HPP

#include <auxiliary/VectorUtils.hpp>
#include <core/Scene/Camera.hpp>
#include "SceneNode.hpp"

namespace mach::core {
	class SceneHierarchy;

	typedef std::shared_ptr<SceneHierarchy> ScenePtr;
	typedef std::shared_ptr<SceneNode<float>> NodePtr;

	class SceneHierarchy {
		std::vector<NodePtr> m_base_nodes;

		std::shared_ptr<Camera<float>> m_main_camera;

	public:
		explicit SceneHierarchy(
				const std::shared_ptr<Camera<float>> &p_main_camera = std::make_shared<Camera<float>>())
				: m_main_camera(
				p_main_camera) {

		}

		static void add_node(ScenePtr &p_hierarchy, NodePtr &p_node) {
			if (p_hierarchy && p_node) {
				auto it = std::find(p_hierarchy->m_base_nodes.begin(), p_hierarchy->m_base_nodes.end(), p_node);
				if (it == p_hierarchy->m_base_nodes.end()) {
					p_hierarchy->m_base_nodes.push_back(p_node);
					p_node->scene = p_hierarchy;
					p_node->transform->parent = std::weak_ptr<TransformCompound<float>>(); //Basically a nullptr
				}
			}
		}

		void remove_node(const NodePtr &p_node) {
			VectorUtils::remove_all_instances_of_val(m_base_nodes, p_node);
		}

		std::size_t get_base_node_count() {
			return m_base_nodes.size();
		}

		std::size_t get_total_nodes() {
			std::size_t total = 0;
			for (const auto &node: m_base_nodes) {
				total += node->transform->get_children_count_deep();
			}
			if (m_main_camera) {
				total++;
				total += m_main_camera->transform->get_children_count_deep();
			}
			return total;
		}

		void update() {
			Logger::log("Scene Hierarchy update!");
			for (int i = m_base_nodes.size() - 1; i >= 0; --i) {
				m_base_nodes[i]->update();
			}
			if (m_main_camera) {
				m_main_camera->update();
			}
		}
	};
}

#endif //MACH_SCENEHIERARCHY_HPP
