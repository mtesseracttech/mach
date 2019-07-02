//
// Created by mtesseract on 6/25/19.
//

#ifndef MACH_OPENGLRENDERER_HPP
#define MACH_OPENGLRENDERER_HPP

#include <graphics/shaders/OpenGLShader.hpp>
#include <graphics/geometry/Mesh.hpp>
#include "Renderer.hpp"

namespace mach::gfx {
	class OpenGLRenderer : public Renderer {
		void render_scene() override;

		void setup() override;

		friend class Renderer;

	protected:

	};

}


#endif //MACH_OPENGLRENDERER_HPP
