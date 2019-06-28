#include <iostream>
#include <graphics/window/OpenGLWindow.hpp>
#include <graphics/renderer/OpenGLRenderer.hpp>
#include "io/input/KeyInput.hpp"
#include "io/input/MouseInput.hpp"
#include "MachApplication.hpp"
#include "../tests/TestRunner.hpp"

namespace mach {

	MachApplication::MachApplication() {
		m_window = gfx::RenderWindow::create<gfx::OpenGLWindow>();
		m_renderer = gfx::Renderer::create<gfx::OpenGLRenderer>();
		setup_subsystems();
	}

	void MachApplication::setup_subsystems() {
		KeyInput::setup(*m_window, 1.0 / 60);
		MouseInput::setup(*m_window, 1.0 / 60);
	}

	void MachApplication::run() {
		m_renderer->setup();

		while (!m_window->is_closing()) {
			if (KeyInput::enter(Escape)) {
				m_window->close();
			}
			m_window->clear(0.2, 0.3, 0.3, 1.0);
			m_renderer->render_scene();
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

