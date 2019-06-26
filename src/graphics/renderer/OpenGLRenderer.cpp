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
				Vec3(-0.5f, -0.5f, 0.0f),
				Vec3(0.5f, -0.5f, 0.0f),
				Vec3(0.0f, 0.5f, 0.0f)
		};
		m_base_shader.load_shader_module("base");
	}

	void OpenGLRenderer::render_scene() {
		//Logger::log("Rendering with OpenGL");
	}
}
