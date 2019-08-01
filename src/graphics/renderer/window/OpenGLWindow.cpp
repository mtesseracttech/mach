//
// Created by mtesseract on 23-5-19.
//
#include "OpenGLWindow.hpp"

namespace mach::gfx {
	OpenGLWindow::OpenGLWindow(std::string p_window_title, uint32_t p_width, uint32_t p_height) : RenderWindow(
			p_window_title, p_width, p_height) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		auto window = glfwCreateWindow(p_width, p_height, p_window_title.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);

		if (!window) {
			glfwTerminate();
			Logger::log("Failed to create an OpenGL window", Error);
		} else {
			glfwMakeContextCurrent(window);

			if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
				Logger::log("Failed to initialize GLAD", Error);
			}

			glfwSetFramebufferSizeCallback(window, glfw_resize_window_callback);
			//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			m_glfw_window = window;
			Logger::log("Successfully Created a GLFW/OpenGL window!", Info);
		}
	}

	void OpenGLWindow::swap_buffers() {
		if (m_glfw_window) {
			glfwSwapBuffers(m_glfw_window);
		}
	}

	void OpenGLWindow::resize_framebuffer(uint32_t p_width, uint32_t p_height) {
		resize_viewport(p_width, p_height);
	}

	void OpenGLWindow::resize_viewport(uint32_t p_width, uint32_t p_height) {
		m_width = p_width;
		m_height = p_height;
		glViewport(0, 0, p_width, p_height);
	}

	void OpenGLWindow::clear(float p_r, float p_g, float p_b, float p_a) {
		glClearColor(p_r, p_g, p_b, p_a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLWindow::set_cursor_mode(CursorMode p_mode) {
		if(m_glfw_window){
			switch (p_mode){
				case Visible:
					glfwSetInputMode(m_glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					break;
				case Invisible:
					glfwSetInputMode(m_glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
					break;
				default:
					break;
			}
		}
	}
}
