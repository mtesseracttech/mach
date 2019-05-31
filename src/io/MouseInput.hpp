//
// Created by mtesseract on 27-5-19.
//

#ifndef MACH_MOUSEINPUT_HPP
#define MACH_MOUSEINPUT_HPP

#include <graphics/window/RenderWindow.hpp>

namespace mach {
	class MouseInput {
	public:
		static bool get_button_down();

		static bool get_button_up();

		static bool get_button();

	protected:

		friend class MachApplication;

		static void setup(RenderWindow &p_window);

		static void glfw_mouse_callback(GLFWwindow *p_window, int p_button, int p_action, int p_mods);

		static void glfw_mouse_pos_callback(GLFWwindow *p_window, double p_x_pos, double p_y_pos);

	private:
	};
}


#endif //MACH_MOUSEINPUT_HPP
