#include <cmath>

#include <iostream>
#include <graphics/window/OpenGLWindow.hpp>
#include <graphics/shaders/OpenGLShader.hpp>
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
		//m_renderer->setup();
		std::array<Vec3, 3> vertices = {
				Vec3(-0.5f, -0.5f, 0.0f),
				Vec3(0.5f, -0.5f, 0.0f),
				Vec3(0.0f, 0.5f, 0.0f)
		};

		std::array<uint32_t, 3> indices = {
				0, 1, 2
		};

		gfx::OpenGLShader shader;
		shader.load_shader_module("base");

		Timer timer;

		unsigned int vbo, vao, ebo;
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void *) 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		while (!m_window->is_closing()) {
			if (KeyInput::enter(Escape)) {
				m_window->close();
			}
			m_window->clear(0.2, 0.3, 0.3, 1.0);

			float time_value = static_cast<float>(timer.get_elapsed());
			float green_value = (std::sin(time_value) / 2.0f) + 0.5f;
			int vertex_color_location = shader.get_uniform_location("ourColor");
			shader.use();
			glUniform4f(vertex_color_location, 0.0f, green_value, 0.0f, 1.0f);
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
			//m_renderer->render_scene();
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

