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
#include "behaviour/camera/FirstPersonCameraBehaviour.hpp"

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

		//auto shader = cache::AssetCache<gfx::OpenGLShader>::get().load_asset("base");
		auto shader = cache::AssetCache<gfx::OpenGLShader>::get().load_asset("phong");

		auto model = cache::AssetCache<gfx::Model<float>>::get().load_asset("nanosuit/nanosuit.obj");

		auto model_transform = std::make_shared<Transform>();
		auto model2_transform = std::make_shared<Transform>();
		model_transform->add_child(model2_transform);
		//model2_transform->local_position = Vec3(10,10,10);

		Timer timer;

		auto scene = core::SceneHierarchy<float>::create(std::make_shared<core::Camera<float>>());
		auto camera = scene->get_main_camera();

		camera->transform->local_position = Vec3(0.0, 8.0, 10.0);
		camera->add_behaviour(std::make_unique<behaviour::FirstPersonCameraBehaviour>(behaviour::FirstPersonCameraBehaviour(50, 1)));

		Vec2 old_mouse_pos = MouseInput::position();
		float previous_time = 0.0;

		while (!m_window->is_closing()) {
			float current_time = timer.get_elapsed();
			float delta_time = current_time - previous_time;
			auto cur_pos = MouseInput::position();
			auto mouse_delta = cur_pos - old_mouse_pos;

			m_window->clear(0.1, 0.1, 0.1, 1.0);

			scene->update(delta_time);

			old_mouse_pos = cur_pos;

			//model_transform->local_rotation *= Quat::from_angle_axis(delta_time, Vec3::up());

			auto camera_view = scene->get_main_camera()->get_view();

			int rows = 1;
			int cols = 1;
			float spacing = 10.0;
			Vec2 middle(spacing * ((float)(cols - 1) / 2.0), spacing * ((float)(rows - 1) / 2.0));
			for(int x = 0; x < cols; ++x){
				for(int y = 0; y < rows; ++y){
					Vec2 position(x * spacing, y * spacing);
					float dist_from_center = Vec2::distance(position, middle);
					model_transform->local_position = Vec3(position.x, std::sin((current_time * 100 + dist_from_center)/spacing) * 2.0, position.y);
					shader->use();
					shader->set_val("view", camera_view);
					shader->set_val("perspective", math::perspective<float>(0.0001, 1000, 90, m_window->get_aspect_ratio()));
					shader->set_val("model", model_transform->get_mat());
					model->draw(*shader);
				}
			}

//			shader->use();
//			shader->set_val("view", camera_view);
//			shader->set_val("perspective", math::perspective<float>(0.0001, 1000, 90, m_window->get_aspect_ratio()));
//			shader->set_val("model", Mat4::identity());
//			model->draw(*shader);
//
//			shader->use();
//			shader->set_val("view", camera_view);
//			shader->set_val("perspective", math::perspective<float>(0.0001, 1000, 90, m_window->get_aspect_ratio()));
//			shader->set_val("model", model_transform->get_mat());
//			model->draw(*shader);
//
//			shader->use();
//			shader->set_val("view", camera_view);
//			shader->set_val("perspective", math::perspective<float>(0.0001, 1000, 90, m_window->get_aspect_ratio()));
//			shader->set_val("model", model2_transform->get_mat());
//			model->draw(*shader);

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