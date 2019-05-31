//
// Created by mtesseract on 23-5-19.
//

#ifndef MACH_RENDERWINDOW_HPP
#define MACH_RENDERWINDOW_HPP

#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "auxiliary/Constants.hpp"


namespace mach {
	class RenderWindow {
	protected:
		GLFWwindow *m_glfw_window = nullptr;
		bool m_closing = false;
	public:
		RenderWindow() : RenderWindow(std::string(mach::Constants::DEF_WIN_NAME)) {}

		RenderWindow(std::string p_window_title) : RenderWindow(p_window_title, mach::Constants::DEF_WIN_WIDTH,
		                                                        mach::Constants::DEF_WIN_HEIGHT) {}

		RenderWindow(uint32_t p_width, uint32_t p_height) : RenderWindow(std::string(mach::Constants::DEF_WIN_NAME),
		                                                                 p_width,
		                                                                 p_height) {}

		RenderWindow(std::string p_window_title, uint32_t p_width, uint32_t p_height) {};

		virtual ~RenderWindow();

		GLFWwindow *get_raw_window() const;

		virtual void close();

		virtual bool is_closing();

		virtual void swap_buffers() = 0;

		virtual void poll_events();

		virtual void set_window_title(std::string p_window_title);

		virtual void set_window_dimensions(uint32_t p_width, uint32_t p_height);

	protected:
		static void glfw_error_callback(int p_err_code, const char *p_err_str);
	};

}


#endif //MACH_RENDERWINDOW_HPP
