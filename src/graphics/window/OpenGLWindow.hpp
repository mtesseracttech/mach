//
// Created by mtesseract on 23-5-19.
//

#ifndef MACH_OPENGLWINDOW_HPP
#define MACH_OPENGLWINDOW_HPP


#include <glad/glad.h>
#include "RenderWindow.hpp"
#include <GLFW/glfw3.h>


namespace mach {
	class OpenGlWindow : public RenderWindow {
	public:
		OpenGlWindow() : OpenGlWindow(std::string(mach::Constants::DEF_WIN_NAME)) {}

		OpenGlWindow(std::string p_window_title) : OpenGlWindow(p_window_title, mach::Constants::DEF_WIN_WIDTH,
		                                                        mach::Constants::DEF_WIN_HEIGHT) {}

		OpenGlWindow(uint32_t p_width, uint32_t p_height) : OpenGlWindow(std::string(mach::Constants::DEF_WIN_NAME),
		                                                                 p_width,
		                                                                 p_height) {}

		OpenGlWindow(std::string p_window_title, uint32_t p_width, uint32_t p_height);

		~OpenGlWindow() override;

		void swap_buffers() override;

	protected:
		static void glfw_resize_window_callback(GLFWwindow *p_window, int p_width, int p_height);
	};
}


#endif //MACH_OPENGLWINDOW_HPP
