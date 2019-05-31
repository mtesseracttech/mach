//
// Created by mtesseract on 27-5-19.
//

#include "KeyInput.hpp"

namespace mach {
	void KeyInput::setup(RenderWindow &p_window) {
		auto window = p_window.get_raw_window();
		if (window) {
			glfwSetKeyCallback(window, glfw_key_callback);
			std::cout << "Set up the keyboard input" << std::endl;
		} else {
			std::cout << "Could not set up the keyboard input, the GLFW window is not defined" << std::endl;
		}
	}

	void KeyInput::glfw_key_callback(GLFWwindow *p_window, int p_key, int p_scancode, int p_action, int mods) {

	}


}