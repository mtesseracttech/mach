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

		m_vertices = {
				Vec3(0.5f, 0.5f, 0.0f),
				Vec3(0.5f, -0.5f, 0.0f),
				Vec3(-0.5f, -0.5f, 0.0f),
				Vec3(-0.5f, 0.5f, 0.0f)
		};
		m_indices = {
				0, 1, 3,
				1, 2, 3
		};

		m_base_shader.load_shader_module("base");
		m_model.load_from_file("../res/models/teapot.obj");
		m_model.generate_normals();

		glGenVertexArrays(1, &m_vao_id);
		glGenBuffers(1, &m_vbo_id);
		glGenBuffers(1, &m_ebo_id);

		glBindVertexArray(m_vao_id);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), &m_vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), &m_indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void *) nullptr);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void OpenGLRenderer::render_scene() {
		m_base_shader.use();
		glBindVertexArray(m_vao_id);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

	}
}
