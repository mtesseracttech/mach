#include <iostream>
#include <math/linalg/Vector2.hpp>
#include "graphics/window/OpenGLWindow.hpp"
#include "io/KeyInput.hpp"
#include "io/MouseInput.hpp"
#include "MachApplication.hpp"

namespace mach {

	MachApplication::MachApplication() {
		m_window = new OpenGlWindow();
		setup_subsystems();
	}

	void MachApplication::setup_subsystems() {
		mach::KeyInput::setup(*m_window);
		mach::MouseInput::setup(*m_window);
	}

	void MachApplication::run() {
		while (!m_window->is_closing()) {
			m_window->swap_buffers();
			m_window->poll_events();
		}
		shutdown();
	}


	void MachApplication::shutdown() {
		m_window->close();
	}

	void MachApplication::test() {
		auto v_0 = Vector2(1.0, 2.0);
		auto v_1 = Vector2(3.0, 4.0);

		std::cout << v_1.length_squared() << std::endl;
		std::cout << v_1.length() << std::endl;

		auto v_2 = v_0 + v_1;

		std::cout << "lol" << std::endl;
		std::cout << "v_2 = " << v_2.x << << std::endl;
	}


}

int main() {
	mach::MachApplication app;
	app.test();
	//app.run();
}

