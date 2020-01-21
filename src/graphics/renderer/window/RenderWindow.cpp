
//
// Created by mtesseract on 23-5-19.
//

#include "RenderWindow.hpp"


namespace mach::gfx {
	GLFWwindow *RenderWindow::get_raw_window() const {
		return m_glfw_window;
	}

	RenderWindow::~RenderWindow() {
		if (m_glfw_window) {
			Logger::log("Destroying the rendering window and terminating GLFW");
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
		std::stringstream ss;
		ss << "GLFW Error: " << p_err_code << " description: " << p_err_str;
		Logger::log(ss.str(), LogType::Error);
	}

	void RenderWindow::glfw_resize_window_callback(GLFWwindow *p_window, int p_width, int p_height) {
		Logger::log("Resizing window");
		auto *window = reinterpret_cast<RenderWindow *>(glfwGetWindowUserPointer(p_window));
		if (window) {
			window->resize_framebuffer(p_width, p_height);
		} else {
			mach_assert(false, "The window user pointer that the resize callback got is somehow null");
		}
	}

	void RenderWindow::poll_events() {
		glfwPollEvents();
	}

	RenderWindow::RenderWindow(const std::string& p_window_title, uint32_t p_width, uint32_t p_height) : m_window_title(p_window_title), m_width(p_width), m_height(p_height)  {
		glfwSetErrorCallback(glfw_error_callback);

		if (glfwInit() == GL_FALSE) {
			Logger::log("GLFW Failed to initialize successfully", Error);
		} else {
			Logger::log("GLFW initialized successfully", Info);
		}
	}

	IVec2 RenderWindow::get_window_dimensions() {
		return IVec2(m_width, m_height);
	}

	float RenderWindow::get_aspect_ratio() const {
		return (float)m_width / (float)m_height;
	}
}
