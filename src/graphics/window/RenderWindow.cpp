
//
// Created by mtesseract on 23-5-19.
//

#include "RenderWindow.hpp"


namespace mach {
	GLFWwindow *RenderWindow::get_raw_window() const {
		return m_glfw_window;
	}

	RenderWindow::~RenderWindow() {
		if (m_glfw_window) {
			glfwDestroyWindow(m_glfw_window);
			glfwTerminate();
		}
	}

	void RenderWindow::close() {
		if (m_glfw_window) glfwSetWindowShouldClose(m_glfw_window, true);
		m_closing = true;
	}

	bool RenderWindow::is_closing() {
		return !m_glfw_window || glfwWindowShouldClose(m_glfw_window) || m_closing;
	}

	void RenderWindow::set_window_title(std::string p_window_title) {
		if (m_glfw_window) {
			glfwSetWindowTitle(m_glfw_window, p_window_title.c_str());
		}
	}

	void RenderWindow::set_window_dimensions(uint32_t p_width, uint32_t p_height) {
		if (m_glfw_window) {
			glfwSetWindowSize(m_glfw_window, p_width, p_height);
		}
	}

	void RenderWindow::glfw_error_callback(int p_err_code, const char *p_err_str) {
		std::cout << "GLFW Error: " << p_err_code << " description: " << p_err_str << std::endl;
	}

	void RenderWindow::poll_events() {
		glfwPollEvents();
	}
}
