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
#include "math/linalg/Matrix/MatrixUtils.hpp"
#include "math/linalg/Rotations.hpp"
#include "core/scene/behaviour/FirstPersonCameraBehaviour.hpp"

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
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		auto shader = cache::AssetCache<gfx::OpenGLShader>::get().load_asset("base");
		auto model = cache::AssetCache<gfx::Model<float>>::get().load_asset("nanosuit/nanosuit.obj");

		Transform model_transform;

		float camera_speed = 20.0;

		Timer timer;

		auto scene = core::SceneHierarchy<float>::create(std::make_shared<core::Camera<float>>());
		auto camera = scene->get_main_camera();

		camera->transform->local_position = Vec3(0.0, 8.0, 10.0);
		camera->add_behaviour(std::make_unique<core::FirstPersonCameraBehaviour>(core::FirstPersonCameraBehaviour(5, 50)));

		Vec2 old_mouse_pos = MouseInput::position();
		float previous_time = 0.0;

		while (!m_window->is_closing()) {
			m_window->clear(0.1, 0.1, 0.1, 1.0);

			auto win_dims = m_window->get_window_dimensions();
			float aspect_ratio = (float) win_dims.x / (float) win_dims.y;
			float current_time = timer.get_elapsed();
			float delta_time = current_time - previous_time;
			auto cur_pos = MouseInput::position();
			auto mouse_delta = cur_pos - old_mouse_pos;

			scene->update(delta_time);

			old_mouse_pos = cur_pos;

			shader->use();
			shader->set_val("model", model_transform.get_mat());
			shader->set_val("view", scene->get_main_camera()->get_view());
			shader->set_val("perspective", math::perspective<float>(0.0001, 1000, 90, aspect_ratio));
			model->draw(*shader);

			previous_time = current_time;

			m_window->swap_buffers();
			m_window->poll_events();

			if (KeyInput::enter(Escape)) {
				m_window->close();
			}
		}
		shutdown();
	}

	void MachApplication::shutdown() {
		m_window->close();
	}


}

int main() {
	//std::cout << mach::get_execution_path() << std::endl;
	mach::tests::run_tests();
	mach::MachApplication app;
	app.run();
}