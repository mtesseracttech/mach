//
// Created by mtesseract on 23-5-19.
//
#include "OpenGLWindow.hpp"

namespace mach {
	OpenGlWindow::OpenGlWindow(std::string p_window_title, uint32_t p_width, uint32_t p_height) : RenderWindow(
			p_window_title, p_width, p_height) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		auto window = glfwCreateWindow(p_width, p_height, p_window_title.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);

		if (!window) {
			glfwTerminate();
			Logger::log("Failed to create an OpenGL window", LogError);
		} else {
			glfwMakeContextCurrent(window);

			if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
				Logger::log("Failed to initialize GLAD", LogError);
			}

			glfwSetFramebufferSizeCallback(window, glfw_resize_window_callback);

			m_glfw_window = window;
			Logger::log("Successfully Created a GLFW/OpenGL window!", LogInfo);
		}
	}

	void OpenGlWindow::swap_buffers() {
		if (m_glfw_window) {
			glfwSwapBuffers(m_glfw_window);
		}
	}

	void OpenGlWindow::resize_framebuffer(uint32_t p_width, uint32_t p_height) {
		resize_viewport(p_width, p_height);
	}

	void OpenGlWindow::resize_viewport(uint32_t p_width, uint32_t p_height) {
		glViewport(0, 0, p_width, p_height);
	}

	void OpenGlWindow::clear(float p_r, float p_g, float p_b, float p_a) {
		glClearColor(p_r, p_g, p_b, p_a);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}
