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

		auto scene = SceneHierarchy<float>::create();
		auto node0 = SceneNode<float>::create(scene, "Node0");
		auto node1 = SceneNode<float>::create(node0, "Node1");

		mach_assert(scene->get_total_nodes() == 3, "Total nodes should be 3 at this point");
		node0->transform->add_child(node1->transform);
		mach_assert(scene->get_total_nodes() == 3, "And Now as well");


		scene->update();
	}
}

#endif //MACH_COREENGINETESTS_HPP
