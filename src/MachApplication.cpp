#include <iostream>
#include "graphics/window/OpenGLWindow.hpp"
#include "io/input/KeyInput.hpp"
#include "io/input/MouseInput.hpp"
#include "MachApplication.hpp"
#include "../tests/TestRunner.hpp"

namespace mach {

	MachApplication::MachApplication() {
		m_window = gfx::RenderWindow::create_window<gfx::OpenGlWindow>();
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

		uint32_t vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
//		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);


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
	}
}

int main() {
	mach::tests::run_tests();
	mach::MachApplication app;
	app.run();
}

