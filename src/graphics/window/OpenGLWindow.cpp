//
// Created by mtesseract on 23-5-19.
//
#include "OpenGLWindow.hpp"

namespace mach {
	OpenGlWindow::OpenGlWindow(std::string p_window_title, uint32_t p_width, uint32_t p_height) : RenderWindow(
			p_window_title, p_width, p_height) {

		glfwSetErrorCallback(glfw_error_callback);

		if (glfwInit() == GL_FALSE) {
			std::cout << "GLFW did not initialize successfully" << std::endl;
		} else {
			std::cout << "GLFW did initialize successfully" << std::endl;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

		auto window = glfwCreateWindow(p_width, p_height, p_window_title.c_str(), nullptr, nullptr);

		if (!window) {
			glfwTerminate();
			throw "Could not initialize an GLFW/OpenGL window!";
		} else {
			glfwMakeContextCurrent(window);

			if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
				throw "Failed to initialize GLAD";
			}

			glfwSetFramebufferSizeCallback(window, glfw_resize_window_callback);

			m_glfw_window = window;
			std::cout << "Successfully Created a GLFW/OpenGL window!" << std::endl;
		}
	}

	OpenGlWindow::~OpenGlWindow() {
		if (m_glfw_window) {
			std::cout << "Destroying the OpenGL window!" << std::endl;
			glfwDestroyWindow(m_glfw_window);
			glfwTerminate();
		}
	}

	void OpenGlWindow::glfw_resize_window_callback(GLFWwindow *p_window, int p_width, int p_height) {
		glViewport(0, 0, p_width, p_height);
	}

	void OpenGlWindow::swap_buffers() {
		if (m_glfw_window) {
			glfwSwapBuffers(m_glfw_window);
		}
	}

}
