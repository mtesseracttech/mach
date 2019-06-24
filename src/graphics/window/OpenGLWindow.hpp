#include <utility>

//
// Created by mtesseract on 23-5-19.
//

#ifndef MACH_OPENGLWINDOW_HPP
#define MACH_OPENGLWINDOW_HPP


#include <glad/glad.h>
#include "RenderWindow.hpp"
#include <GLFW/glfw3.h>


namespace mach::gfx {
	class OpenGlWindow : public RenderWindow {
	protected:
		OpenGlWindow() : OpenGlWindow(std::string(mach::Constants::DEF_WIN_NAME)) {}

		explicit OpenGlWindow(std::string p_window_title) : OpenGlWindow(std::move(p_window_title),
		                                                                 mach::Constants::DEF_WIN_WIDTH,
		                                                                 mach::Constants::DEF_WIN_HEIGHT) {}

		OpenGlWindow(uint32_t p_width, uint32_t p_height) : OpenGlWindow(std::string(mach::Constants::DEF_WIN_NAME),
		                                                                 p_width,
		                                                                 p_height) {}

		OpenGlWindow(std::string p_window_title, uint32_t p_width, uint32_t p_height);

		friend class RenderWindow;

	public:
		void swap_buffers() override;

		void clear(float p_r, float p_g, float p_b, float p_a) override;

	protected:
		//Called by the glfw callback
		void resize_framebuffer(uint32_t p_width, uint32_t p_height) override;

		void resize_viewport(uint32_t p_width, uint32_t p_height) override;
	};
}


#endif //MACH_OPENGLWINDOW_HPP
