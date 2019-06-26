//
// Created by mtesseract on 6/25/19.
//

#ifndef MACH_OPENGLRENDERER_HPP
#define MACH_OPENGLRENDERER_HPP

#include <graphics/shaders/OpenGLShader.hpp>
#include "Renderer.hpp"

namespace mach::gfx {
	class OpenGLRenderer : public Renderer {
		void render_scene() override;

		void setup() override;

		friend class Renderer;

	protected:
		std::array<Vec3, 3> m_vertices;
		OpenGLShader m_base_shader;
	};

}


#endif //MACH_OPENGLRENDERER_HPP
