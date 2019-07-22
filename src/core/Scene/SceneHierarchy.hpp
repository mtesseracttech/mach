//
// Created by mtesseract on 7/21/19.
//

#ifndef MACH_SCENEHIERARCHY_HPP
#define MACH_SCENEHIERARCHY_HPP

#include <auxiliary/VectorUtils.hpp>
#include <core/Scene/Camera.hpp>
#include "SceneNode.hpp"

namespace mach::core {


	typedef std::shared_ptr<SceneNode<float>> NodePtr;

	template<typename T>
	class SceneHierarchy : std::enable_shared_from_this<SceneHierarchy<T>> {
	protected:
		std::vector<NodePtr> m_base_nodes;

		std::shared_ptr<Camera<T>> m_main_camera;

	public:
		explicit SceneHierarchy(const std::shared_ptr<Camera<T>> &p_main_camera) : m_main_camera(p_main_camera) {}

		static std::shared_ptr<SceneHierarchy>
		create(const std::shared_ptr<Camera<T>> &p_main_camera = std::make_shared<Camera<T>>()) {
			return std::make_shared<SceneHierarchy>(p_main_camera);
		}

		std::shared_ptr<SceneHierarchy> get_ptr() {
			return this->shared_from_this();
		}

		void add_node(NodePtr &p_node) {
			if (p_node) {
				auto it = std::find(m_base_nodes.begin(), m_base_nodes.end(), p_node);
				if (it == m_base_nodes.end()) {
					m_base_nodes.push_back(p_node);
					p_node->scene = this->weak_from_this();
					p_node->transform->parent = std::weak_ptr<TransformCompound<float>>(); //Basically a nullptr
				}
			}
		}

		std::shared_ptr<Camera<T>> get_main_camera() {
			return m_main_camera;
		}

		void remove_node(const NodePtr &p_node) {
			VectorUtils::remove_all_instances_of_val(m_base_nodes, p_node);
		}

		std::size_t get_base_node_count() {
			return m_base_nodes.size();
		}

		std::size_t get_total_nodes() {
			std::size_t total = get_base_node_count();
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
