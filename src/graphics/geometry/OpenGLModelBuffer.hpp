//
// Created by mtesseract on 6/26/19.
//

#ifndef MACH_OPENGLMODELBUFFER_HPP
#define MACH_OPENGLMODELBUFFER_HPP

#include <math/linalg/LinAlgTypes.hpp>
#include <vector>
#include <glad/glad.h>
#include <graphics/model/Mesh.hpp>
#include "graphics/model/Vertex.hpp"


namespace mach::gfx {
	template<typename AttribType, typename = std::enable_if_t<std::is_floating_point<AttribType>::value>>
	class OpenGLModelBuffer {
	public:
		OpenGLModelBuffer(const Mesh<AttribType> &p_mesh) {
			m_indices = p_mesh.m_indices;
			m_vertices.reserve(p_mesh.m_vertices.size());
			for (std::size_t i = 0; i < m_vertices.size(); ++i) {
				Vertex vtx = {Vector3<AttribType>::zero(), Vector3<AttribType>::zero(), Vector2<AttribType>::zero()};
				if (i < p_mesh.m_vertices.size()) vtx.m_position = p_mesh.m_vertices[i];
				if (i < p_mesh.m_normals.size()) vtx.m_normal = p_mesh.m_normals[i];
				if (i < p_mesh.m_texture_coords.size()) vtx.m_position = p_mesh.m_texture_coords[i];
				m_vertices.push_back(vtx);
			}
		}

	protected:
		std::vector<uint32_t> m_indices;
		std::vector<Vertex<AttribType>> m_vertices;
		uint32_t m_vbo_id = 0;
		uint32_t m_vao_id = 0;
		uint32_t m_ebo_id = 0;
	public:

		void generate_buffers() {
			glGenVertexArrays(1, &m_vao_id);
			glGenBuffers(1, &m_vbo_id);
			glGenBuffers(1, &m_ebo_id);
			glBindVertexArray(m_vao_id);

			glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
			glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex<AttribType>), m_vertices.data(),
			             GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32_t), m_indices.data(),
			             GL_STATIC_DRAW);

			if constexpr (std::is_same<AttribType, float>::value) {
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<AttribType>),
				                      (void *) offsetof(Vertex<AttribType>, m_position));
				glEnableVertexAttribArray(0);

				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<AttribType>),
				                      (void *) offsetof(Vertex<AttribType>, m_normal));
				glEnableVertexAttribArray(1);

				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex<AttribType>),
				                      (void *) offsetof(Vertex<AttribType>, m_tex_coords));
				glEnableVertexAttribArray(2);

			} else if constexpr (std::is_same<AttribType, double>::value) {
				glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(Vertex<AttribType>),
				                      (void *) offsetof(Vertex<AttribType>, m_position));
				glEnableVertexAttribArray(0);

				glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, sizeof(Vertex<AttribType>),
				                      (void *) offsetof(Vertex<AttribType>, m_normal));
				glEnableVertexAttribArray(1);

				glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, sizeof(Vertex<AttribType>),
				                      (void *) offsetof(Vertex<AttribType>, m_tex_coords));
				glEnableVertexAttribArray(2);
			} else {
				throw NotImplemented("No other attribute types except for float and double are implemented");
			}

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void draw() {
			glBindVertexArray(m_vao_id);
			glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
	};
}


#endif //MACH_OPENGLMODELBUFFER_HPP
