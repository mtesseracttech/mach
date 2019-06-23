//
// Created by mtesseract on 27-5-19.
//

#include "KeyInput.hpp"

namespace mach {
	bool                 KeyInput::m_prepared = false;
	double               KeyInput::m_time_step = 1.0 / 60;
	std::map<int, float> KeyInput::m_keys;
	Timer                KeyInput::m_timer;

	void KeyInput::setup(RenderWindow &p_window, double p_time_step) {
		auto window = p_window.get_raw_window();
		m_time_step = p_time_step;
		if (window) {
			glfwSetKeyCallback(window, glfw_key_callback);
			m_prepared = true;
			std::cout << "Set up the keyboard input" << std::endl;
		} else {
			std::cout << "Could not set up the keyboard input, the GLFW window is not defined" << std::endl;
		}
	}

	void KeyInput::glfw_key_callback(GLFWwindow *p_window, int p_key, int p_scancode, int p_action, int mods) {
		switch (p_action) {
			case GLFW_PRESS:
				key_down(p_key);
				break;
			case GLFW_RELEASE:
				key_up(p_key);
				break;
			default:
				break;
		}
	}

	//Key State Management
	void KeyInput::key_up(int p_key) {
		m_keys[p_key] = 0.0f;
	}

	void KeyInput::key_down(int p_key) {
		auto it = m_keys.find(p_key);

		if (it != m_keys.end() || m_keys[p_key] == 0.0f) {
			m_keys[p_key] = static_cast<float>(m_timer.get_elapsed());
		}
	}

	//Public Accessible Functions
	bool KeyInput::enter(KeyCode p_key) {
		if (!m_prepared) return false;
		auto it = m_keys.find(p_key);
		if (it != m_keys.end()) {
			return m_keys[p_key] > m_timer.get_elapsed() - m_time_step;
		}
		return false;
	}

	bool KeyInput::pressed(KeyCode p_key) {
		if (!m_prepared) return false;
		auto it = m_keys.find(p_key);
		if (it != m_keys.end()) {
			return m_keys[p_key] > 0.0f;
		}
		return false;
	}

}