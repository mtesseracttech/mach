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
		std::array<Vec3, 6> vertices = {
				Vec3(0.5, -.5, 0.0), Vec3(1, 0, 0),
				Vec3(-.5, -.5, 0.0), Vec3(0, 1, 0),
				Vec3(0.0, 0.5, 0.0), Vec3(0, 0, 1)
		};

		std::array<Vec2, 3> tex_coords = {
				Vec2(0.0, 0.0),
				Vec2(1.0, 0.0),
				Vec2(0.5, 1.0)
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

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vec3), (void *) 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(Vec3), (void *) sizeof(Vec3));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		while (!m_window->is_closing()) {
			if (KeyInput::enter(Escape)) {
				m_window->close();
			}
			m_window->clear(0.2, 0.3, 0.3, 1.0);

			auto time_value = static_cast<float>(timer.get_elapsed());
			Vec4 color((std::sin(time_value) / 2.0f) + 0.5f,
			           (std::sin(time_value + math::pi / 3 * 2) / 2.0f) + 0.5f,
			           (std::sin(time_value + math::pi / 3 * 4) / 2.0f) + 0.5f, 1.0f);


			shader.use();
			shader.set_vec4("ourColor", color);
			shader.set_val("offset", std::sin(time_value));

			//glUniform4f(vertex_color_location, 0.0f, green_value, 0.0f, 1.0f);
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

