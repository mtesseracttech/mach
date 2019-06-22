#include <iostream>
#include "graphics/window/OpenGLWindow.hpp"
#include "io/KeyInput.hpp"
#include "io/MouseInput.hpp"
#include "MachApplication.hpp"
#include "tests/TestRunner.hpp"

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
}

int main() {
	mach::tests::run_tests();
	mach::MachApplication app;
	app.run();
}

