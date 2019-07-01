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
		std::array<uint32_t, 2> m_vbo_ids;
		std::array<uint32_t, 2> m_vao_ids;
		std::array<uint32_t, 2> m_ebo_ids;
		std::array<Vec3, 3> m_vertices;
		std::array<Vec3, 3> m_vertices2;

		std::array<uint32_t, 6> m_indices;
		OpenGLShader m_base_shader;
		OpenGLShader m_base2_shader;

		WaveformObj<float> m_model;
		Mesh<float> *m_mesh;
	};

}


#endif //MACH_OPENGLRENDERER_HPP
