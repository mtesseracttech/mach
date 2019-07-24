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
#include <math/linalg/LinAlgTypes.hpp>


namespace mach::gfx {
	class RenderWindow {
	protected:
		GLFWwindow *m_glfw_window = nullptr;
		bool m_closing = false;

		uint32_t m_width = 0;
		uint32_t m_height = 0;
		float m_aspect_ratio = 0;

		RenderWindow(std::string p_window_title, uint32_t p_width, uint32_t p_height);

		virtual ~RenderWindow();

	public:

		GLFWwindow *get_raw_window() const;

		virtual void close();

		virtual bool is_closing();

		virtual void clear(float p_r, float p_g, float p_b, float p_a) = 0;

		virtual void swap_buffers() = 0;

		virtual void poll_events();

		virtual void set_window_title(std::string p_window_title);

		virtual void set_window_dimensions(uint32_t p_width, uint32_t p_height);

		IVec2 get_window_dimensions();

		float get_aspect_ratio();

	protected:
		virtual void resize_framebuffer(uint32_t p_width, uint32_t p_height) = 0;

		virtual void resize_viewport(uint32_t p_width, uint32_t p_height) = 0;

		static void glfw_error_callback(int p_err_code, const char *p_err_str);

		static void glfw_resize_window_callback(GLFWwindow *p_window, int p_width, int p_height);

	public:
		template<typename WindowType>
		static std::shared_ptr<WindowType>
		create_window(std::string p_window_title, uint32_t p_width, uint32_t p_height) {
			return std::shared_ptr<WindowType>(new WindowType(p_window_title, p_width, p_height));
		};

		template<typename WindowType>
		static std::shared_ptr<WindowType> create_window(uint32_t p_width, uint32_t p_height) {
			return create_window<WindowType>(std::string(mach::Constants::DEF_WIN_NAME),
			                                 p_width,
			                                 p_height);
		}

		template<typename WindowType>
		static std::shared_ptr<WindowType> create_window(std::string p_window_title) {
			return create_window<WindowType>(std::move(p_window_title),
			                                 mach::Constants::DEF_WIN_WIDTH,
			                                 mach::Constants::DEF_WIN_HEIGHT);
		}

		template<typename WindowType>
		static std::shared_ptr<WindowType> create() {
			return create_window<WindowType>(std::string(mach::Constants::DEF_WIN_NAME));
		}
	};

}


#endif //MACH_RENDERWINDOW_HPP
