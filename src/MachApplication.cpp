#include <cmath>

#include <iostream>
#include <graphics/window/OpenGLWindow.hpp>
#include <graphics/shaders/OpenGLShader.hpp>
#include <graphics/renderer/OpenGLRenderer.hpp>
#include <graphics/texture/OpenGLTexture.hpp>
#include "io/input/KeyInput.hpp"
#include "io/input/MouseInput.hpp"
#include "MachApplication.hpp"
#include "../tests/TestRunner.hpp"

namespace mach {
	MachApplication::MachApplication() {
		m_window = gfx::RenderWindow::create<gfx::OpenGLWindow>();
//		m_renderer = gfx::Renderer::create<gfx::OpenGLRenderer>();
		setup_subsystems();
	}

	void MachApplication::setup_subsystems() {
		KeyInput::setup(*m_window, 1.0 / 60);
		MouseInput::setup(*m_window, 1.0 / 60);
	}

	void MachApplication::run() {
		struct VBO {
			Vec3 vertex;
			Vec3 color;
			Vec2 texture_coord;
		};

		std::array<VBO, 4> vbos = {
				VBO{Vec3(0.5, 0.5, 0.0), Vec3(1, 0, 0), Vec2(1, 1)},
				VBO{Vec3(0.5, -.5, 0.0), Vec3(0, 1, 0), Vec2(1, 0)},
				VBO{Vec3(-.5, -.5, 0.0), Vec3(0, 0, 1), Vec2(0, 0)},
				VBO{Vec3(-.5, 0.5, 0.0), Vec3(1, 1, 0), Vec2(0, 1)}
		};

		std::array<uint32_t, 6> indices = {
				0, 1, 2, 2, 3, 0
		};

		gfx::OpenGLShader shader;
		shader.load_shader_module("base");

		gfx::OpenGLTexture channel_tex;
		channel_tex.load_from_file("test_kanaal.png");

		gfx::OpenGLTexture other_tex;
		std::cout << other_tex.load_from_file("") << std::endl;

		Timer timer;

		unsigned int vbo, vao, ebo;
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vbos), vbos.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VBO), (void *) offsetof(VBO, vertex));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VBO), (void *) offsetof(VBO, color));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VBO), (void *) offsetof(VBO, texture_coord));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		while (!m_window->is_closing()) {
			if (KeyInput::enter(Escape)) {
				m_window->close();
			}
			m_window->clear(0.2, 0.3, 0.3, 1.0);

			auto time_value = static_cast<float>(timer.get_elapsed());
			Vec3 color((std::sin(time_value) / 2.0f) + 0.5f,
			           (std::sin(time_value + math::pi / 3 * 2) / 2.0f) + 0.5f,
			           (std::sin(time_value + math::pi / 3 * 4) / 2.0f) + 0.5f);

			shader.use();
			shader.set_val("test_color", color);

			channel_tex.bind_texture();
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
	try {
		mach::tests::run_tests();
		mach::MachApplication app;
		app.run();
	} catch (const std::exception &ex) {
		mach::Logger::log(ex.what(), mach::Error);
	}

}

