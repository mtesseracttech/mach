#include <iostream>
#include "graphics/window/OpenGLWindow.hpp"
#include "io/input/KeyInput.hpp"
#include "io/input/MouseInput.hpp"
#include "MachApplication.hpp"
#include "../tests/TestRunner.hpp"

namespace mach {

	MachApplication::MachApplication() {
		m_window = new OpenGlWindow();
		setup_subsystems();
	}

	void MachApplication::setup_subsystems() {
		KeyInput::setup(*m_window, 1.0 / 60);
		MouseInput::setup(*m_window, 1.0 / 60);
	}

	void MachApplication::run() {
		Vec3 vertices[] = {
				Vec3(-0.5f, -0.5f, 0.0f),
				Vec3(0.5f, -0.5f, 0.0f),
				Vec3(0.0f, 0.5f, 0.0f)
		};

		Timer timer;
		timer.get_time_in_hh_mm_ss();

		uint32_t vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


		while (!m_window->is_closing()) {
			if (KeyInput::enter(Escape)) {
				m_window->close();
			}

			m_window->clear(0.2, 0.3, 0.3, 1.0);
			m_window->swap_buffers();
			m_window->poll_events();
		}
		shutdown();
	}


	void MachApplication::shutdown() {
		m_window->close();
		delete m_window;
	}
}

int main() {
	mach::tests::run_tests();
	mach::MachApplication app;
	app.run();
}

