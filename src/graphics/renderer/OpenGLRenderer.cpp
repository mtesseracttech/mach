//
// Created by mtesseract on 6/25/19.
//

#include <auxiliary/logging/Logger.hpp>
#include <math/linalg/LinAlgTypes.hpp>
#include <io/files/FileIO.hpp>
#include <glad/glad.h>
#include "OpenGLRenderer.hpp"
#include <string>


namespace mach::gfx {
	void OpenGLRenderer::setup() {
		Logger::log("Setting up OpenGL renderer");
	}

	void OpenGLRenderer::render_scene() {
	}
}
