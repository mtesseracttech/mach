//
// Created by mtesseract on 27-5-19.
//

#ifndef MACH_KEYINPUT_HPP
#define MACH_KEYINPUT_HPP

#include <graphics/window/RenderWindow.hpp>

namespace mach {
	class KeyInput {
	public:
		static bool get_key_down();

		static bool get_key_up();

		static bool get_key();

	protected:

		friend class MachApplication;

		static void setup(RenderWindow &p_window);

		static void glfw_key_callback(GLFWwindow *p_window, int p_key, int p_scancode, int p_action, int p_mods);

	private:
	};
}


#endif //MACH_KEYINPUT_HPP
