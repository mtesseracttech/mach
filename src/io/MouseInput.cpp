//
// Created by mtesseract on 27-5-19.
//

#include "MouseInput.hpp"

namespace mach {
	void MouseInput::setup(RenderWindow &p_window) {
		auto window = p_window.get_raw_window();
		if (window) {
			glfwSetMouseButtonCallback(window, glfw_mouse_callback);
			glfwSetCursorPosCallback(window, glfw_mouse_pos_callback);
			std::cout << "Set up the mouse input" << std::endl;
		} else {
			std::cout << "Could not set up the mouse input, the GLFW window is not defined" << std::endl;
		}

	}

	void MouseInput::glfw_mouse_callback(GLFWwindow *p_window, int p_button, int p_action, int p_mods) {

	}

	void MouseInput::glfw_mouse_pos_callback(GLFWwindow *p_window, double p_x_pos, double p_y_pos) {

	}
}