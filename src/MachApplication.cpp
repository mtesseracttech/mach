#include <cmath>

#include <iostream>
#include <graphics/renderer/window/OpenGLWindow.hpp>
#include <graphics/renderer/shaders/OpenGLShader.hpp>
#include <graphics/renderer/OpenGLRenderer.hpp>
#include <graphics/renderer/texture/OpenGLTexture.hpp>
#include <graphics/renderer/model/Model.hpp>
#include <caching/AssetCache.hpp>
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

		auto shader = cache::AssetCache<gfx::OpenGLShader>::get().load_asset("base");
		auto model = cache::AssetCache<gfx::Model<float>>::get().load_asset("nanosuit/nanosuit.obj");

		Timer timer;

		while (!m_window->is_closing()) {
			if (KeyInput::enter(Escape)) {
				m_window->close();
			}
			m_window->clear(0.2, 0.3, 0.3, 1.0);

			model->draw(*shader);


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
//	try {
	mach::tests::run_tests();
	mach::MachApplication app;
	app.run();
//	} catch (const std::exception &ex) {
//		mach::Logger::log(ex.what(), mach::Error);
//	}

}

