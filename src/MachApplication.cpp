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

		float camera_speed = 1.0;

		Timer timer;

		auto scene = core::SceneHierarchy<float>::create(std::make_shared<core::Camera<float>>());
		auto camera = scene->get_main_camera();

		camera->transform->local_position = Vec3(0.0, 8.0, 10.0);

		Vec2 old_mouse_pos;

		while (!m_window->is_closing()) {
			auto win_dims = m_window->get_window_dimensions();
			float aspect_ratio = (float) win_dims.x / (float) win_dims.y;
			float delta_time = timer.get_elapsed();
			auto cur_pos = MouseInput::position();
			auto mouse_delta = cur_pos - old_mouse_pos;

			if (KeyInput::enter(Escape)) {
				m_window->close();
			}

			float movement_speed = delta_time * 0.1;
			if (KeyInput::pressed(W)) {
				camera->transform->local_position += camera->transform->backward * movement_speed;
			}
			if (KeyInput::pressed(S)) {
				camera->transform->local_position += camera->transform->forward * movement_speed;
			}
			if (KeyInput::pressed(A)) {
				camera->transform->local_position += camera->transform->left * movement_speed;
			}
			if (KeyInput::pressed(D)) {
				camera->transform->local_position += camera->transform->right * movement_speed;
			}

			if (MouseInput::pressed(Button1)) {
				float mouse_speed = delta_time * 0.001;
				Vec2 rotation_deltas = Vec2(mouse_delta.x, mouse_delta.y) * mouse_speed;
				RotationMatrix<float> cur_rotation = RotationMatrix<float>::from_quat(camera->transform->rotation);
				RotationMatrix<float> around_x = RotationMatrix<float>::from_angle_axis(rotation_deltas.y,
				                                                                        cur_rotation.right().normalized());
				RotationMatrix<float> around_y = RotationMatrix<float>::from_angle_axis(rotation_deltas.x,
				                                                                        cur_rotation.up().normalized());
				camera->transform->local_rotation *= Quat::from_matrix(around_x.to_mat3() * around_y.to_mat3());

//				Quat around_x = Quat::from_angle_axis(rotation_deltas.y, Vec3::right());
//				Quat around_y = Quat::from_angle_axis(rotation_deltas.x, Vec3::up());
//				Quat added_rotation = around_x * around_y;
//
//				camera->transform->local_rotation *= added_rotation;
//
//				std::cout << camera->transform->local_rotation << std::endl;
//				std::cout << camera->transform->local_rotation.magnitude_squared() << std::endl;
			}

			m_window->clear(0.2, 0.3, 0.3, 1.0);

			old_mouse_pos = cur_pos;

			shader->use();
			shader->set_val("model", Mat4::identity());
			shader->set_val("view", scene->get_main_camera()->get_view());
			shader->set_val("perspective", math::perspective<float>(0.0001, 1000, 90, aspect_ratio));
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
	//std::cout << mach::get_execution_path() << std::endl;
	mach::tests::run_tests();
	mach::MachApplication app;
	app.run();
}