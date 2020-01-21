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

		gfx::CursorMode cursor_mode = gfx::Visible;

		auto phong_shader = cache::AssetCache<gfx::OpenGLShader>::get().load_asset("phong");
		auto lighting_shader = cache::AssetCache<gfx::OpenGLShader>::get().load_asset("flat");

		auto nanosuit_model = cache::AssetCache<gfx::Model<float>>::get().load_asset("nanosuit/nanosuit.obj");
		auto light_model = cache::AssetCache<gfx::Model<float>>::get().load_asset("sphere.obj");
		auto quad_model = cache::AssetCache<gfx::Model<float>>::get().load_asset("quad.obj");

		auto model_transform = std::make_shared<Transform>();
		auto light_transform = std::make_shared<Transform>();
		auto ground_transform = std::make_shared<Transform>();

		light_transform->local_position(Vec3(2,10,5));
		light_transform->local_scale(Vec3(1.0/40.0));


		ground_transform->local_rotation(Quat::from_angle_axis(math::to_rad(90.0), Vec3::right()));
		ground_transform->local_scale(Vec3(20));

		Timer timer;

		auto scene = core::SceneHierarchy<float>::create(std::make_shared<core::Camera<float>>());
		auto camera = scene->get_main_camera();

		camera->transform()->local_position(Vec3(0.0, 8.0, 10.0));

		auto camera_behaviour = std::make_shared<behaviour::FirstPersonCameraBehaviour>(5, 50, 0.1);
		camera->add_behaviour(camera_behaviour);
		camera_behaviour->set_cursor_mode(cursor_mode);

		Vec2 old_mouse_pos = MouseInput::position();
		float previous_time = 0.0;

		while (!m_window->is_closing()) {
			float current_time = timer.get_elapsed();
			float delta_time = current_time - previous_time;
			auto cur_pos = MouseInput::position();
			auto mouse_delta = cur_pos - old_mouse_pos;

			m_window->clear(0.1, 0.1, 0.1, 0.1);

			scene->update(delta_time);

			old_mouse_pos = cur_pos;

			light_transform->local_position(Vec3(std::sin(current_time) * 5, light_transform->local_position().y(), std::cos(current_time) * 5));

			auto view = scene->get_main_camera()->view();
			auto perspective = math::perspective<float>(0.01, 1000, math::to_rad(90), m_window->get_aspect_ratio());
			auto cam_pos = scene->get_main_camera()->transform()->world_position();

			phong_shader->use();
			phong_shader->set_val("camera_position", camera->transform()->world_position());
			phong_shader->set_val("material.specular", Vec3(1.0));
			phong_shader->set_val("material.shininess", 8.f);
			phong_shader->set_val("light.position", light_transform->world_position());
			phong_shader->set_val("light.ambient",  Vec3(0.2));
			phong_shader->set_val("light.diffuse",  Vec3(0.5));
			phong_shader->set_val("light.specular", Vec3(1.0));
			phong_shader->set_val("view", view);
			phong_shader->set_val("perspective", perspective);
			phong_shader->set_val("model", model_transform->matrix());
			nanosuit_model->draw(*phong_shader);


			phong_shader->set_val("model", ground_transform->matrix());
			quad_model->draw(*phong_shader);

			lighting_shader->use();
			lighting_shader->set_val("color", Vec3(1.0));
			lighting_shader->set_val("view", view);
			lighting_shader->set_val("perspective", perspective);
			lighting_shader->set_val("model", light_transform->matrix());
			light_model->draw(*lighting_shader);

			previous_time = current_time;

			m_window->swap_buffers();
			m_window->poll_events();

			if (KeyInput::enter(Escape)) {
				m_window->close();
			}
			if(KeyInput::enter(C)){ //Cursor mode swapping
				switch(cursor_mode){
					case gfx::Visible:
						m_window->set_cursor_mode(gfx::Invisible);
						cursor_mode = gfx::Invisible;
						break;
					case gfx::Invisible:
						m_window->set_cursor_mode(gfx::Visible);
						cursor_mode = gfx::Visible;
						break;
				}
				camera_behaviour->set_cursor_mode(cursor_mode);
			}
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