//
// Created by mtesseract on 27-5-19.
//

#ifndef MACH_MOUSEINPUT_HPP
#define MACH_MOUSEINPUT_HPP

#include <map>
#include <graphics/renderer/window/RenderWindow.hpp>
#include <math/linalg/LinAlgTypes.hpp>
#include <auxiliary/time/Timer.hpp>

namespace mach {
	enum MouseButton {
		Button1 = GLFW_MOUSE_BUTTON_1,
		Button2 = GLFW_MOUSE_BUTTON_2,
		Button3 = GLFW_MOUSE_BUTTON_3,
		Button4 = GLFW_MOUSE_BUTTON_4,
		Button5 = GLFW_MOUSE_BUTTON_5
	};

	class MouseInput {
	public:
		//User Functionality

		/*
		 * Returns true for a given mouse button approximately for 1 frame (60 fps taken as a base line)
		 */
		static bool enter(MouseButton p_button);

		/*
		 * Returns true as long as the given mouse button is pressed
		 */
		static bool pressed(MouseButton p_button);

		/*
		 * Gets the position of the mouse pointer
		 */
		static Vec2 position();

	protected:
		static bool m_prepared;
		static std::map<int, float> m_buttons;
		static Timer m_timer;
		static double m_time_step;
		static Vec2 m_position;

		//GLFW callbacks
		static void glfw_mouse_button_callback(GLFWwindow *p_window, int p_button, int p_action, int p_mods);

		static void glfw_mouse_pos_callback(GLFWwindow *p_window, double p_x_pos, double p_yPos);

		//Button Cache management functions
		static void button_up(int p_button);

		static void button_down(int p_button);

		//Technical functionality to be used by gamebase
		friend class MachApplication;

		static void setup(const gfx::RenderWindow &p_window, double p_time_step = 1.0 / 60.0);
	};
}


#endif //MACH_MOUSEINPUT_HPP
