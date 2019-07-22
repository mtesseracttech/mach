//
// Created by mtesseract on 7/22/19.
//

#ifndef MACH_COREENGINETESTS_HPP
#define MACH_COREENGINETESTS_HPP

#include <iostream>
#include <auxiliary/MachAssertion.hpp>
#include <core/Scene/SceneHierarchy.hpp>
#include <core/Scene/SceneNode.hpp>

namespace mach::tests::core {
	class CoreEngineTests {
	public:
		static void run_tests();

		static void scene_tests();
	};

	void CoreEngineTests::run_tests() {
		Logger::log("CORE ENGINE TESTS:");
		scene_tests();
	}

	void CoreEngineTests::scene_tests() {
		Logger::log("SCENE HIERARCHY TESTS");


		using namespace mach::core;

		auto scene = SceneHierarchy<float>::create(std::make_shared<Camera<float>>());
		auto node0 = SceneNode<float>::create(scene, "Node0");
		auto node1 = SceneNode<float>::create(node0, "Node1");
		mach_assert(scene->get_total_nodes() == 3, "Total nodes should be 3 at this point, 2 nodes, 1 camera");
		node0->transform->add_child(node1->transform);
		mach_assert(scene->get_total_nodes() == 3, "And Now as well");
		auto node2 = SceneNode<float>::create(node1, "Node2");
		mach_assert(scene->get_total_nodes() == 4, "Total nodes should be 4 at this point, 4, ");
		auto node3 = SceneNode<float>::create(node1, "Node3");
		mach_assert(scene->get_total_nodes() == 5, "Total nodes should be 5 at this point, 4, ");


		scene->update();
	}
}

#endif //MACH_COREENGINETESTS_HPP
