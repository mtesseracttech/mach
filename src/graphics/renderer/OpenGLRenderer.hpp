//
// Created by mtesseract on 6/25/19.
//

#ifndef MACH_OPENGLRENDERER_HPP
#define MACH_OPENGLRENDERER_HPP

#include <graphics/shaders/OpenGLShader.hpp>
#include <graphics/geometry/Mesh.hpp>
#include <graphics/model/WaveformObj.hpp>
#include "Renderer.hpp"

namespace mach::gfx {
	class OpenGLRenderer : public Renderer {
		void render_scene() override;

		void setup() override;

		friend class Renderer;

	protected:
		uint32_t m_vbo_id = 0;
		uint32_t m_vao_id = 0;
		uint32_t m_ebo_id = 0;
		std::array<Vec3, 4> m_vertices;
		std::array<uint32_t, 6> m_indices;
		OpenGLShader m_base_shader;
		WaveformObj<float> m_model;
	};

}


#endif //MACH_OPENGLRENDERER_HPP
