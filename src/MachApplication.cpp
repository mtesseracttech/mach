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

		//auto phong_shader = cache::AssetCache<gfx::OpenGLShader>::get().load_asset("base");
		auto phong_shader = cache::AssetCache<gfx::OpenGLShader>::get().load_asset("phong");
		auto lighting_shader = cache::AssetCache<gfx::OpenGLShader>::get().load_asset("flat");

		auto nanosuit_model = cache::AssetCache<gfx::Model<float>>::get().load_asset("nanosuit/nanosuit.obj");
		auto light_model = cache::AssetCache<gfx::Model<float>>::get().load_asset("sphere.obj");

		auto model_transform = std::make_shared<Transform>();
		auto light_transform = std::make_shared<Transform>();

		light_transform->local_position = Vec3(2,10,5);
		light_transform->local_scale = Vec3(1.0/40.0);

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

			m_window->clear(1, 1, 1, 1);

			scene->update(delta_time);

			old_mouse_pos = cur_pos;

			model_transform->local_rotation *= Quat::from_angle_axis(delta_time, Vec3::up());

			auto camera_view = scene->get_main_camera()->get_view();

			model_transform->local_rotation = Quat::from_angle_axis(current_time, Vec3::up());
			phong_shader->use();
			phong_shader->set_val("object_color", Vec3(1.0, 0.5, 0.31));
			phong_shader->set_val("light_color", Vec3(1.0, 1.0, 1.0));
			phong_shader->set_val("light_pos", light_transform->position);
			phong_shader->set_val("view", camera_view);
			phong_shader->set_val("perspective", math::perspective<float>(0.0001, 1000, math::to_rad(90), m_window->get_aspect_ratio()));
			phong_shader->set_val("model", model_transform->get_mat());
			nanosuit_model->draw(*phong_shader);

			lighting_shader->use();
			lighting_shader->set_val("color", Vec3(0.8, 0.8, 0));
			lighting_shader->set_val("view", camera_view);
			lighting_shader->set_val("perspective", math::perspective<float>(0.0001, 1000, math::to_rad(90), m_window->get_aspect_ratio()));
			lighting_shader->set_val("model", light_transform->get_mat());
			light_model->draw(*lighting_shader);

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