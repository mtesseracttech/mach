//
// Created by mtesseract on 6/25/19.
//

#include <auxiliary/logging/Logger.hpp>
#include <math/linalg/LinAlgTypes.hpp>
#include <io/FileIO.hpp>
#include <glad/glad.h>
#include "OpenGLRenderer.hpp"
#include <string>


namespace mach::gfx {
	void OpenGLRenderer::setup() {
		Logger::log("Setting up OpenGL renderer");

//		m_vertices = {
//				Vec3(0.5f, 0.5f, 0.0f),
//				Vec3(0.5f, -0.5f, 0.0f),
//				Vec3(-0.5f, -0.5f, 0.0f),
//				Vec3(-0.5f, 0.5f, 0.0f)
//		};
//		m_indices = {
//				0, 1, 3,
//				1, 2, 3
//		};
//
//		Vec3 offset(0.5, 0, 0);
//
//		m_vertices = {
//				Vec3(-0.5f, -0.5f, 0.0f) - offset,
//				Vec3(0.5f, -0.5f, 0.0f) - offset,
//				Vec3(0.0f, 0.5f, 0.0f) - offset
//		};
//
//		m_vertices2 = {
//				Vec3(-0.5f, -0.5f, 0.0f) + offset,
//				Vec3(0.5f, -0.5f, 0.0f) + offset,
//				Vec3(0.0f, 0.5f, 0.0f) + offset
//		};
//
//		m_indices = {
//				0, 1, 2,
//				3, 4, 5
//		};
//
//		m_base_shader.load_shader_module("base");
//		m_base2_shader.load_shader_module("base2");

		m_model.load_from_file("../res/models/teapot.obj");
		m_model.generate_normals();

//		m_mesh = new Mesh<float>(m_model);
//		m_mesh->generate_buffers();
//
//		glGenVertexArrays(2, m_vao_ids.data());
//		glGenBuffers(2, m_vbo_ids.data());
//
//		glGenBuffers(1, &m_ebo_id);
//
//		glBindVertexArray(m_vao_ids[0]);
//		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_ids[0]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices.data(), GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void *) nullptr);
//		glEnableVertexAttribArray(0);
//
//		glBindVertexArray(m_vao_ids[1]);
//		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_ids[1]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices2), m_vertices2.data(), GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void *) nullptr);
//		glEnableVertexAttribArray(0);
//
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindVertexArray(0);
	}

	void OpenGLRenderer::render_scene() {
		m_base_shader.use();
		m_mesh->draw();
//		glBindVertexArray(m_vao_ids[0]);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//		m_base2_shader.use();
//		glBindVertexArray(m_vao_ids[1]);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		//glBindVertexArray(0);
	}
}
