//
// Created by mtesseract on 27-5-19.
//

#include "MouseInput.hpp"

namespace mach {
	bool                 MouseInput::m_prepared = false;
	double               MouseInput::m_time_step = 1.0 / 60;
	std::map<int, float> MouseInput::m_buttons;
	Timer                MouseInput::m_timer;
	Vec2                 MouseInput::m_position = Vec2::zero();

	void MouseInput::setup(RenderWindow &p_window, double p_time_step) {
		auto window = p_window.get_raw_window();
		m_time_step = p_time_step;
		if (window) {
			glfwSetMouseButtonCallback(window, glfw_mouse_button_callback);
			glfwSetCursorPosCallback(window, glfw_mouse_pos_callback);
			m_prepared = true;
			std::cout << "Set up the mouse input" << std::endl;
		} else {
			std::cout << "Could not set up the mouse input, the GLFW window is not defined" << std::endl;
		}
	}

	void MouseInput::glfw_mouse_button_callback(GLFWwindow *p_window, int p_button, int p_action, int p_mods) {
		switch (p_action) {
			case GLFW_PRESS:
				button_down(p_button);
				break;
			case GLFW_RELEASE:
				button_up(p_button);
				break;
			default:
				break;
		}
	}

	void MouseInput::glfw_mouse_pos_callback(GLFWwindow *p_window, double p_x, double p_y) {
		m_position.x = p_x;
		m_position.y = p_y;
	}

	void MouseInput::button_up(int p_button) {
		m_buttons[p_button] = 0.0f;
	}

	void MouseInput::button_down(int p_button) {
		auto it = m_buttons.find(p_button);

		if (it != m_buttons.end() || m_buttons[p_button] == 0.0f) {
			m_buttons[p_button] = static_cast<float>(m_timer.get_elapsed());
		}
	}

	Vec2 MouseInput::position() {
		return m_position;
	}

	bool MouseInput::enter(MouseButton p_button) {
		if (!m_prepared) return false;
		auto it = m_buttons.find(p_button);
		if (it != m_buttons.end()) {
			return m_buttons[p_button] > static_cast<float>(m_timer.get_elapsed()) - m_time_step;
		}
		return false;
	}

	bool MouseInput::pressed(MouseButton p_button) {
		if (!m_prepared) return false;
		auto it = m_buttons.find(p_button);
		if (it != m_buttons.end()) {
			return m_buttons[p_button] > 0.0f;
		}
		return false;
	}
}